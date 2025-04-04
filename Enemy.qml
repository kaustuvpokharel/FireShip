import QtQuick

Item {

    property var ePng: [
        "qrc:/enemy/enemy1.png",
        "qrc:/enemy/enemy2.png",
        "qrc:/enemy/enemy3.png",
        "qrc:/enemy/enemy4.png",
        "qrc:/enemy/enemy5.png"
    ]

    property int eIndex: 0

    id: enemy1
    width: 50
    height: 50
    x: model.x
    y: model.y

    Image
    {
        id: enemies
        anchors.fill: parent
        source: ePng[model.mIndex]
    }

}
