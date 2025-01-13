import QtQuick
import QtQuick.Layouts
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("joystick")

    GridLayout{
        id:gird
        columns:1
        Text {
            id: name
            text: "X: " + serialReader.vrX;
        }
        Text {
            id: name2
            text: "Y: " + serialReader.vrY;
        }
    }

    Rectangle{
        id: circle
        radius: 180
        anchors.centerIn: parent
        width: 200
        height: 200
        color: "white"
        border.color: "black";
        border.width: 2

        Rectangle{
            id: origin
            anchors.centerIn: parent
            radius: 180
            width: 10
            height: 10
            color: "red"


        }

        Rectangle{
            id: joystick
            x: parent.width/2 - 10 + (serialReader.vrY * parent.width/2)
            y: parent.height/2 - 10 - (serialReader.vrX * parent.width/2)
            radius: 180
            width: 20
            height: 20
            color: "green"


        }

    }

}
