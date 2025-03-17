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

        Keys.onReleased: (event) =>
                         {
                            if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                             {
                                control.stopMovement()
                             }
                         }
    }

    Text{
        id: scoreBoard
        text: "Score:" + control.showScore()
        color: "black"
        x: 50
        y: 50

        Connections
        {
            target: control
            function onScoreChanged()
            {
                scoreBoard.text = "Score:" + control.showScore();
            }
        }
    }


    Repeater
    {
        model: control.bullets
        delegate: Bullet{}
    }

    Repeater
    {
        model: control.enemies
        delegate: Enemy{}
    }
}
