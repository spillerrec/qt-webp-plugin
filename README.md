# qt5-webp-plugin

WebP plugin for Qt5 image loading

## Features
- Reading
- Writing Lossless when Quality == 100
- Writing Lossy when Quality <= 99. Quality is passed to libwebp in the range 1 to 100.

## Building

*Dependencies*
- Qt5
- qmake
- libwebp

*Building*
1 qmake
2 make

*Installation*
After successful compilation you should have a webp.* file (extension dependent on OS). You can install this globally or application specific. If the file is placed in Qt's plug-in folder under *imageformats*, it will be available to all Qt5 applications. To only use it with a specific application, create a folder called *imageformats* in the executables folder and place the plug-in there.