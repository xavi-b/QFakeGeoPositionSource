import QtQuick 2.5
import QtQuick.Controls 2.14
import QtLocation 5.14
import QtPositioning 5.14

ApplicationWindow {
    id: appWindow
    width: 1024
    height: 640
    visible: true

    property var port: 50000
    property var host: "localhost"

    PositionSource {
        id: src
        updateInterval: 500
        active: false
        name: "fake"

        PluginParameter { name: "port"; value: port }
        PluginParameter { name: "host"; value: host }

        Component.onCompleted: {
            console.log("PositionSource ready");
            src.start();
        }

        onPositionChanged: {
            poiCurrent.coordinate = src.position.coordinate;
            map.center = src.position.coordinate;
            console.log("Coordinate:", poiCurrent.coordinate.longitude, poiCurrent.coordinate.latitude);
        }

        onSourceErrorChanged: {
            console.log("Error: " + sourceError);
        }

        onUpdateTimeout: {
            console.log("Update timeout");
        }
    }

    Page {
        anchors.fill: parent

        header: ToolBar {

        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            zoomLevel: 20

            Plugin {
                id: mapPlugin
                name: "osm"
            }

            MapQuickItem {
                id: poiCurrent
                sourceItem: Rectangle { width: 14; height: 14; color: "#1e25e4"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                opacity: 1.0
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }

        }
    }
}
