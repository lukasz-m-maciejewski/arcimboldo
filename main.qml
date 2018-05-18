import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    header: RowLayout {
        id: topRow

        Button {
            id: button

            text: qsTr("Button")
        }
    }

    ScrollView {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom:  parent.bottom
        id: scrollView

        width: Math.min(0.3 * parent.width, 300)

        ListView {
            anchors.fill: parent
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }

    }

    Image {
        id: image
        fillMode: Image.PreserveAspectFit
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: scrollView.right
        anchors.right: parent.right
        source: "file:/home/lukaszm/qt-projects/photo-selector/img/cat.jpg"
    }



    //    RowLayout {
    //        anchors.fill: parent
    //        id: row
    //    }

    //    GridLayout {
    //        id: mainGrid
    //        anchors.fill: parent
    //        columns: 2

    //        ListView {
    //            anchors.fill: parent
    //            model: 20
    //            delegate: ItemDelegate {
    //                text: "Item " + (index + 1)
    //                width: parent.width
    //            }
    //        }

    //        ScrollView {
    //            id: scrollView
    //            Layout.fillHeight: true
    //            Layout.fillWidth: true
    //            anchors.fill: parent
    //        }

    //        Image {
    //            id: previewArea
    //            width: 300
    //            height: 400
    //            source: "file:/home/lukaszm/qt-projects/photo-selector/img/cat.png"
    //        }

    //        Button {
    //            id: placeholderButton
    //            text : qsTr("Qt is shit")
    //        }
    //    }

}
