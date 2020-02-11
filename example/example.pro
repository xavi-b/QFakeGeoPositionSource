TEMPLATE        = app
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += serialport qml quick positioning location
TARGET          = $$PWD/../run_example

SUBDIRS += \
    src/ \
    qml/

include(src/src.pri)
include(qml/qml.pri)

RESOURCES += \
    example.qrc
