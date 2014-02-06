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

#include <QImageIOHandler>
#include <QImageIOPlugin>

class WebpPlugin: public QImageIOPlugin{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QImageIOHandlerFactoryInterface" FILE "extensions.json")
	
	public:
		QStringList keys() const;
		Capabilities capabilities( QIODevice *device, const QByteArray &format ) const;
		QImageIOHandler* create( QIODevice *device, const QByteArray &format = QByteArray() ) const;
};