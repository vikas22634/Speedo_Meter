import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12
import QtQuick.Controls 1.4

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("SpeedoMeter")


    Rectangle {
        id: dashboardId
        height: 500
        width: 1000
        color: "#232332" // background color
        anchors.centerIn: parent

        Button {
            id: myButton
            text: "click"
            anchors {
                top: speedrect.bottom
                horizontalCenter: parent.horizontalCenter

            }



            Rectangle {
                width: myButton.width
                height: myButton.height
                color: "#7077A1" // Set the background color for the button
                radius: 10
                Text {
                    anchors.centerIn: parent
                    text: myButton.text
                    color: "white" // Set the text color
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Change the background color of the ApplicationWindow
                        dashboardId.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                    }
                }
            }
        }






// left and right indicator
            Row {
                id: rowIndicator
                spacing: dashboardId.width * 0.2
                anchors.top: dashboardId.top
                anchors.topMargin: dashboardId.width * 0.06
                anchors.horizontalCenter: parent.horizontalCenter


                ArrowIndicator {
                    id: leftIndicatorId
                    height: dashboardId.height * 0.05
                    width: height * 1.5


                    direction: Qt.LeftArrow
                }

                Rectangle {
                    height: dashboardId.height * 0.05
                    width: height
                    color: "transparent"
                }

                ArrowIndicator {
                    id: rightIndicatorId
                    height: dashboardId.height * 0.05
                    width: height * 1.5
                    direction: Qt.RightArrow
                }

            }

            Row {
                id: dashboardRowId
                spacing: dashboardId.width * 0.02
                anchors.top: rowIndicator.bottom
                anchors.horizontalCenter: parent.horizontalCenter


  //it is the speedometer arcCircle
                CircularGauge {
                    id: speedometerId
                    value: EngineConfigCPP.getSpeed
                    width: height
                    height: dashboardId.height * 0.6
                    maximumValue: 180


                    style: SpedometerStyle{}

                    property bool acceleration: false
                    Component.onCompleted: forceActiveFocus()
                    Rectangle {
                         id: bigCircleId
                         width: 320
                         height: 320
                         anchors.centerIn:parent

                         color: "transparent"
                         border.color: "#0a2f4a"
                         border.width: 2
                         radius: width*0.8
                    }
                    Glow {
                            anchors.fill: bigCircleId
                            radius: 8
                            samples: 17
                            color: "white"
                            source: bigCircleId
                        }

                }



            }

           // Distance Digit in KM
            Rectangle {
                id: speedrect
                height: dashboardId.height * 0.05
                width: dashboardId.width * 0.1
                color: "transparent"
                radius: height * 0.2

                anchors.right: parent.right
                anchors.rightMargin: dashboardId.width * 0.3
                anchors.top: dashboardRowId.bottom

                Text {
                    id: speedrectText
                    text: EngineConfigCPP.getDistance + " km"
                    font.pointSize: 25
                    color: "white"
                    font.bold: true

                }
            }


          // It is the code of EventHandler like for speed you have to press upKey

            Keys.onUpPressed: {
                            EngineConfigCPP.applyBrake(false);
                            EngineConfigCPP.accelerate(true);
                            speedometerId.acceleration = true
                        }

                        Keys.onDownPressed: {
                            EngineConfigCPP.applyBrake(true);
                            EngineConfigCPP.accelerate(false);
                        }

                        Keys.onLeftPressed: {
                            leftIndicatorId.isOn = true
                            rightIndicatorId.isOn = false
                        }

                        Keys.onRightPressed: {
                            rightIndicatorId.isOn = true
                            leftIndicatorId.isOn = false
                        }

                        Keys.onDigit0Pressed: {
                            rightIndicatorId.isOn = false
                            leftIndicatorId.isOn = false
                        }


                        Keys.onReleased: {
                            if (event.key === Qt.Key_Up) {
                                EngineConfigCPP.accelerate(false);
                                speedometerId.acceleration = false
                                event.accepted = true
                            } else if (event.key === Qt.Key_Down) {
                                EngineConfigCPP.applyBrake(false);
                                event.accepted = true
                            }


                        }

                        Loader {
                            id: centralPanelLoader
                            anchors.centerIn: parent
                            width: parent.width
                        }


        }
}



