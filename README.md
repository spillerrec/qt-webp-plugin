# qt-webp-plugin

Enables Qt4 and Qt5 applications to load and save images in the WebP image format.

**NOTICE** Since version 5.3, Qt is bundled with a WebP plugin. You might need to install the qt5-imageformats package (or similar) to get it. See https://github.com/ArchangelSDY/qwebpa for a fork with animation support.
For Qt 4, you would still need this or https://github.com/stevenyao/webp .

### Features

- Reading WebP images
- Writing Lossless WebP images when Quality == 100
- Writing Lossy WebP images when Quality <= 99. Quality is passed to libwebp in the range 1 to 100.

### Building

**Dependencies**

- Qt
- qmake
- libwebp

**Building**

1. qmake
2. make

**Installation**

After successful compilation you should have a webp.* file (extension dependent on OS). You can install this globally or application specific. To install it globally, copy it to *QTDIR/plugins/imageformats/*. To only use it with a specific application, create a folder called *imageformats* in the executable's folder and place the plug-in there.
