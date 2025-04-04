import QtQuick

Item
{
    id: bullet1
    width: 10
    height: 30
    x: model.x
    y: model.y

    Image
    {
        id: bullets
        anchors.fill: parent
        source: "qrc:/bullet/bullet.png"
    }
}
