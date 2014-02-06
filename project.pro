TARGET  = $$qtLibraryTarget(webp)
TEMPLATE = lib
CONFIG += plugin
LIBS += -lwebp

SOURCES = src/WebpPlugin.cpp
HEADERS = src/WebpPlugin.hpp
OTHER_FILES += extensions.json