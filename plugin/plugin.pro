TARGET = $$PWD/../qtposition_fake

QT = core positioning network

unix {
target.path = /usr/lib/qt/plugins/position/
INSTALLS += target
}

HEADERS += \
    qgeopositioninfosource_fake_p.h \
    qgeopositioninfosourcefactory_fake.h

SOURCES += \
    qgeopositioninfosource_fake.cpp \
    qgeopositioninfosourcefactory_fake.cpp

OTHER_FILES += \
    plugin.json

PLUGIN_TYPE = position
PLUGIN_CLASS_NAME = QGeoPositionInfoSourceFactoryFake

TEMPLATE    = lib
CONFIG     += plugin
