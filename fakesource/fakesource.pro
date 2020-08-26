TEMPLATE        = app
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += network qml quick positioning location
TARGET          = $$PWD/../run_fakesource

SUBDIRS += \
    src/ \
    qml/

include(src/src.pri)
include(qml/qml.pri)

RESOURCES += \
    fakesource.qrc
