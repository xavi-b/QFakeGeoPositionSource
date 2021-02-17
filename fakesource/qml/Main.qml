import QtQuick 2.5
import QtQuick.Controls 2.14
import QtLocation 5.14
import QtPositioning 5.14

ApplicationWindow {
    id: appWindow
    width: 1024
    height: 640
    visible: true

    function toggle() {
        console.log("toggle");
        if(timer.running) {
            timer.stop();
            timer.modelIndex = 0;
            timer.pathIndex = 0;
        } else {
            currentCoordinates = startCoordinates;
            routeQuery.clearWaypoints();
            routeQuery.addWaypoint(startCoordinates);
            routeQuery.addWaypoint(endCoordinates);
            routeModel.update();
            map.fitViewportToMapItems();
        }
    }

    function formatTime(sec) {
        var value = sec
        var seconds = value % 60
        value /= 60
        value = (value > 1) ? Math.round(value) : 0
        var minutes = value % 60
        value /= 60
        value = (value > 1) ? Math.round(value) : 0
        var hours = value
        if (hours > 0) value = hours + "h:"+ minutes + "m"
        else value = minutes + "min"
        return value
    }

    function formatDistance(meters) {
        var dist = Math.round(meters)
        if (dist > 1000 ){
            if (dist > 100000){
                dist = Math.round(dist / 1000)
            }
            else{
                dist = Math.round(dist / 100)
                dist = dist / 10
            }
            dist = dist + " km"
        }
        else{
            dist = dist + " m"
        }
        return dist
    }

    property var startCoordinates: QtPositioning.coordinate(59.9485, 10.7686) // Oslo
    property var endCoordinates: QtPositioning.coordinate(59.9645, 10.671)
    property alias currentCoordinates: poiCurrent.coordinate

    property var speedKMH: 30 // km/h
    property var speedMS: speedKMH * 1000 / 3600 // m/s

    signal coordinatesChanged(double lat, double lon);

    onCurrentCoordinatesChanged: {
        coordinatesChanged(currentCoordinates.latitude, currentCoordinates.longitude);
    }

    Page {
        anchors.fill: parent

        header: ToolBar {
            Button {
                id: startBtn
                anchors.left: parent.left
                text: timer.running ? "Stop" : "Start"
                onClicked: toggle();
            }
        }

        Timer {
            id: timer
            interval: 1000
            running: false
            repeat: true

            property var modelIndex: 0
            property var pathIndex: 0

            onTriggered: {
                if (routeModel.count > 0) {
                    if(modelIndex + 1 > routeModel.get(0).segments.length) {
                        //timer.stop();
                        modelIndex = 0;
                        pathIndex = 0;
                        return;
                    }

                    var traveledDistance = speedMS * (interval / 1000);

                    if(pathIndex >= routeModel.get(0).segments[modelIndex].path.length) {
                        pathIndex = 0;
                        ++modelIndex;
                    }

                    console.log("[" + (modelIndex+1) + " / " + routeModel.get(0).segments.length + "] " + (pathIndex+1) + " / " + routeModel.get(0).segments[modelIndex].path.length);
                    var nextCoordinates = routeModel.get(0).segments[modelIndex].path[pathIndex];
                    //console.log(JSON.stringify(nextCoordinates));

                    if(currentCoordinates.distanceTo(nextCoordinates) < traveledDistance) {
                        currentCoordinates = QtPositioning.coordinate(nextCoordinates.latitude, nextCoordinates.longitude);
                        ++pathIndex;
                    } else {
                        var azimuth = currentCoordinates.azimuthTo(QtPositioning.coordinate(nextCoordinates.latitude, nextCoordinates.longitude));
                        var coordinates = currentCoordinates.atDistanceAndAzimuth(traveledDistance, azimuth);
                        currentCoordinates = coordinates;
                    }
                } else {
                    timer.stop();
                    modelIndex = 0;
                    pathIndex = 0;
                }
            }
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            zoomLevel: 14

            Plugin {
                id: mapPlugin
                name: "osm"
            }

            RouteQuery {
                id: routeQuery
                travelModes: RouteQuery.CarTravel
                routeOptimizations: RouteQuery.FastestRoute
            }

            RouteModel {
                id: routeModel
                plugin: Plugin {
                    name: "mapbox"
                    PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoieGF2aS1iIiwiYSI6ImNrZTc3cHR5NDFrZmQyem80Zm55NTlrcHkifQ.UlKCHnBI7IjY86s1hq22sQ" }
                }
                query: routeQuery
                autoUpdate: false
                onStatusChanged: {
                    if(status == RouteModel.Error) {
                        console.log("error: " + errorString);
                    }
                    if(status == RouteModel.Ready) {
                        var totalTravelTime = routeModel.count == 0 ? "" : formatTime(routeModel.get(0).travelTime);
                        var totalDistance = routeModel.count == 0 ? "" : formatDistance(routeModel.get(0).distance);

                        console.log("totalTravelTime: " + totalTravelTime);
                        console.log("totalDistance: " + totalDistance);

                        timer.modelIndex = 0;
                        timer.pathIndex = 0;
                        timer.start();
                    }
                }
            }

            MapItemView {
                model: routeModel
                autoFitViewport: true
                delegate: MapRoute {
                    id: route
                    route: routeData
                    line.color: "#95d5fc"
                    line.width: 5
                    smooth: true
                    opacity: 0.8
                }
            }

            MapQuickItem {
                id: poiTheQtComapny
                sourceItem: Rectangle { width: 14; height: 14; color: "#e41e25"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                coordinate: startCoordinates
                opacity: 1.0
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }

            MapQuickItem {
                id: poiCurrent
                sourceItem: Rectangle { width: 14; height: 14; color: "#1e25e4"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                coordinate: startCoordinates
                opacity: 1.0
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }

            MapQuickItem {
                id: poiEnd
                sourceItem: Rectangle { width: 14; height: 14; color: "#1ee425"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                coordinate: endCoordinates
                opacity: 1.0
                anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }
        }
    }
}
