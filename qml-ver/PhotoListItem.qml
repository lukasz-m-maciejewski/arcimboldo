import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: photo_list_item

    property string photo_file_name: ""
    property string photo_file_path: ""
    property bool photo_selected: false

    signal itemMarkToggle()
    signal itemClicked()

    width: 200
    height: 30

    Label {
        id: nameBox
        anchors.top: parent.top
        anchors.left: parent.left
        height: parent.height
        width: 0.7 * parent.width
        anchors.margins: 12
        wrapMode: Label.Wrap
        Text {
            anchors.fill: parent
            id: entryName
            elide: Text.ElideRight
            text: photo_list_item.photo_file_name
        }
        MouseArea {
            anchors.fill: parent
            onClicked: photo_list_item.itemClicked()
        }
    }
    Button {
        text: photo_list_item.photo_selected ? "Y" : "N"
        anchors.left: nameBox.right
        anchors.top: photo_list_item.top
        anchors.bottom: photo_list_item.bottom
        width: 0.3 * parent.width
        onClicked: photo_list_item.itemMarkToggle()
    }
}
