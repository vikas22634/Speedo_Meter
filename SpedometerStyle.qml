import QtQuick 2.12
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12

CircularGaugeStyle {
    id: speedometerStyleId

    function degree2Rad(deg) {
        return deg * (Math.PI / 180)
    }

    // it draw the arccircle of the red line
    background: Canvas {
        onPaint: {
            var ctr = getContext("2d");
            ctr.reset();
            ctr.beginPath();
            ctr.strokeStyle = "red";
            ctr.linewidth = outerRadius * 0.02;

            ctr.arc(outerRadius, outerRadius, outerRadius - ctr.lineWidth / 2,
                    degree2Rad(valueToAngle(120) - 90),degree2Rad(valueToAngle(180) - 90) )
            ctr.stroke();
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: outerRadius * 0.2
        }

    }
    // it will mark tick on the circle for indicating numbers

    tickmark : Rectangle {
        visible: styleData.value < 120 || styleData.value % 10 == 0
        implicitWidth: outerRadius * 0.02
        antialiasing: true
        implicitHeight: outerRadius * 0.06
        color: styleData.value >= 120 ? "#e34c22" : "#e5e5e5"
    }
    // it is for needle

    needle: Rectangle {
        y: outerRadius* 0.15
        implicitWidth: outerRadius * 0.03
        antialiasing: true
        implicitHeight: outerRadius * 0.9
        color: "#e5e5e5"
    }

    //it will mark minorTickmark on the circle for indicating numbers
    minorTickmark: Rectangle {
        visible: styleData.value < 120
        implicitWidth: outerRadius * 0.01
        antialiasing: true
        implicitHeight: outerRadius * 0.03
        color: styleData.value >= 120 ? "#e34c22" : "#e5e5e5"

    }


    foreground: Item {
        // speed Digit in innerCircle
        Text {
            id: speedTextId
            color: "#ffffff"
            font.pixelSize: 25
            horizontalAlignment: Text.AlignRight
            text: speedometerId.value.toString()
            anchors.centerIn: parent
            z:2
            font.bold : true

        }
        // km/h Text in innerCircle
        Text {
            id: unitSpeedId
            text: " km/h"
            color: "white"
            font.pixelSize: 20
            z:2
            anchors.centerIn: parent
            topPadding: 45
            font.bold: true
        }

        // it will create the innerCircle and glow that circle
        Rectangle{
            id:speedId
            color: dashboardId.color
            border.width: 2
            width : outerRadius * 0.8
            height: width
            radius: width /2
            anchors.centerIn: parent
            border.color: "white"

        }
        Glow {
                anchors.fill:speedId
                radius: 8
                samples: 10
                color: "white"
                source:speedId
            }

    }
}
