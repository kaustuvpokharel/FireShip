import QtQuick

Window {
    width: 1512 //
    height: 982
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        id: move1
        width: 50
        height: 50
        color: "red"
        x: control.x //50
        y: control.y
        focus: true

        Keys.onPressed:(event) =>
                       {
                           if(event.key === Qt.Key_Left)
                           {
                                control.moveLeft()
                           }
                           if(event.key === Qt.Key_Right)
                           {
                                control.moveRight()
                           }
                           if(event.key === Qt.Key_Up)
                           {
                                control.applyThrust();
                           }
                           if(event.key === Qt.Key_Space)
                           {
                                control.fireBullet();
                           }

                       }
    }
}
