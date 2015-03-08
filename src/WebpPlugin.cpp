/*
	This file is part of qt5-webp-plugin.

	qt5-webp-plugin is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	qt5-webp-plugin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with qt5-webp-plugin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QImage>
#include <QByteArray>
#include <QImageIOHandler>
#include <QImageIOPlugin>
#include <QColor>
#include <QVariant>

#include "WebpPlugin.hpp"
#include "webp/decode.h"
#include "webp/encode.h"

class WebpHandler: public QImageIOHandler{
	private:
		int quality;
	public:
		WebpHandler( QIODevice *device ){
			setDevice( device );
			setFormat( "webp" );
			quality = 100;
		}
		
		bool canRead() const;
		bool read( QImage *image );
		bool write( const QImage &image );
		
		bool supportsOption( ImageOption option ) const{
			switch( option ){
				case Quality: return true;
				default: return false;
			};
		}
		
		void setOption( ImageOption option, const QVariant& value ){
			if( option == Quality )
				quality = value.toInt();
		}
};

bool WebpHandler::canRead() const{
	return format() == "webp";
}


bool WebpHandler::read( QImage *img_pointer ){
	QByteArray data = device()->readAll();
	int width, height;
	
	uint8_t *raw = WebPDecodeRGBA( (uint8_t*)data.data(), data.size(), &width, &height );
	if( !raw )
		return false;
	
	QImage img( width, height, QImage::Format_ARGB32 );
	for( int iy=0; iy<height; iy++ ){
		QRgb* row = (QRgb*)img.scanLine( iy );
		
		for( int ix=0; ix<width; ix++ ){
			uint8_t *pixel = raw + ( iy*width + ix ) * 4;
			row[ix] = qRgba( pixel[0], pixel[1], pixel[2], pixel[3] );
		}
	}
	
	*img_pointer = img;
	free( raw );
	return true;
}

bool WebpHandler::write( const QImage &img ){
	QImage image = img;
	bool alpha = image.hasAlphaChannel();
	unsigned pixel_count = alpha ? 4 : 3;
	unsigned stride = pixel_count * image.width();
	
	uint8_t* data = new uint8_t[ stride * image.height() ];
	if( !data )
		return false;
	
	//Make sure the input is in ARGB
	if( image.format() != QImage::Format_RGB32 && image.format() != QImage::Format_ARGB32 )
		image = image.convertToFormat( QImage::Format_ARGB32 );
	
	for( int iy=0; iy<image.height(); ++iy ){
		const QRgb* in = (const QRgb*)image.constScanLine( iy );
		uint8_t* out = data + iy*stride;
		
		for( int ix=0; ix<image.width(); ++ix, ++in ){
			*(out++) = qRed( *in );
			*(out++) = qGreen( *in );
			*(out++) = qBlue( *in );
			if( alpha )
				*(out++) = qAlpha( *in );
		}
	}
	
	uint8_t* output = NULL;
	size_t size;
	
	if( quality == 100 ){
		//Lossless
		if( alpha )
			size = WebPEncodeLosslessRGBA( data, image.width(), image.height(), stride, &output );
		else
			size = WebPEncodeLosslessRGB( data, image.width(), image.height(), stride, &output );
	}
	else{
		//Lossy
		if( alpha )
			size = WebPEncodeRGBA( data, image.width(), image.height(), stride, quality+1, &output );
		else
			size = WebPEncodeRGB( data, image.width(), image.height(), stride, quality+1, &output );
	}
	
	delete[] data;
	if( !output || size == 0 )
		return false;
	
	device()->write( (char*)output, size );
	free( output );
	
	return true;
}


QStringList WebpPlugin::keys() const{
	return QStringList() << "webp";
}

QImageIOPlugin::Capabilities WebpPlugin::capabilities( QIODevice *device, const QByteArray &format ) const{
	if( format == "webp" )
		return Capabilities( CanRead | CanWrite );
	else
		return 0;
}

QImageIOHandler* WebpPlugin::create( QIODevice *device, const QByteArray &format ) const{
	return new WebpHandler( device );
}


