import QtQuick
import QtQuick.Layouts

Window {
    width: 1512 //
    height: 982
    visible: true
    title: qsTr("Hello World")

    FontLoader
    {
        id: pMedium
        source: "qrc:/fonts/Doto-ExtraBold.ttf"
    }

    Rectangle
    {
        id: gameArea
        anchors.fill: parent
        visible: true
        gradient: Gradient
        {
            GradientStop { position: 0.0; color: "#132330"}
            GradientStop { position: 1.0; color: "black"}
        }

        Rectangle
        {
            id: gameOverOverlay
            anchors.fill: parent
            visible: false
            color: "Black"
            opacity: 0.8
            z: 1001

            ColumnLayout
            {
                anchors.centerIn: parent
                spacing: 20
                Text {
                    id: gameOver
                    text: qsTr("Game Over\n " + control.showScore())
                    font.family: pMedium.font.family
                    font.weight: pMedium.font.weight
                    font.styleName: pMedium.font.styleName
                    font.pixelSize: 60
                    Layout.alignment: Qt.AlignHCenter
                    color: "white"

                    Connections
                    {
                        target: control
                        function onScoreChanged()
                        {
                            gameOver.text = qsTr("Game Over\n " + control.showScore());
                        }
                    }
                }

                RowLayout
                {
                    spacing: 20
                    Rectangle
                    {
                        id: closeBtn
                        width: 250
                        height: 45
                        color: "gray"
                        radius: 20
                        Text {
                            text: qsTr("Close")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 35
                            color: "white"
                            anchors.centerIn: parent
                        }

                        MouseArea
                        {
                            hoverEnabled: true

                            anchors.fill: parent
                            onEntered:
                            {
                                closeBtn.color = "red"
                            }

                            onExited:
                            {
                                closeBtn.color = "gray"
                            }

                            onClicked:
                            {
                                Qt.quit();
                            }
                        }
                    }
                    Rectangle
                    {
                        id: restartBtn
                        width: 250
                        height: 45
                        color: "gray"
                        radius: 20
                        Text {
                            text: qsTr("Restart")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: pMedium.font.styleName
                            font.pixelSize: 35
                            color: "white"
                            anchors.centerIn: parent
                        }

                        MouseArea
                        {
                            hoverEnabled: true

                            anchors.fill: parent
                            onEntered:
                            {
                                restartBtn.color = "green"
                            }

                            onExited:
                            {
                                restartBtn.color = "gray"
                            }

                            onClicked:
                            {
                                control.restartGame();
                                gameOverOverlay.visible = false;
                            }
                        }
                    }
                }
            }
        }

        Connections
        {
            target: control
            onGameOver:
            {
                gameOverOverlay.visible = true;
            }
        }

        Rectangle
        {
            id: move1
            width: 85
            height: 85
            color: "Transparent"
            x: control.x //50
            y: control.y
            focus: true

            Image {
                id: rocket
                source: "qrc:/player/rocket.png"
                width: 55
                height: 55
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }

            AnimatedImage
            {
                id: thruster
                source: "qrc:/player/thruster.gif"
                width: 30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rocket.bottom
                playing: true
            }

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

                               thruster.playing = true
                           }

            Keys.onReleased: (event) =>
                             {
                                if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                                 {
                                    control.stopMovement()
                                 }
                                 thruster.playing = true
                             }

            Component.onCompleted:
            {
                move1.forceActiveFocus();
                thruster.playing = true;
            }
        }

        Text{
            id: scoreBoard
            text: "SCORE: " + control.showScore()
            font.family: pMedium.font.family
            font.weight: pMedium.font.weight
            font.styleName: pMedium.font.styleName
            font.pixelSize: 40
            color: "White"
            x: 50
            y: 50

            Connections
            {
                target: control
                function onScoreChanged()
                {
                    scoreBoard.text = "SCORE: " + control.showScore();
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
}
