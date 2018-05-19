import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import com.graycatworkshop.photoselector 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")


    FileDialog {
        id: openDirDialog
        title: "Choose dir"
        folder: shortcuts.home

        selectFolder: true
        onAccepted: {
            console.log("folder is now: " + folder)
            sidelist.model.currentDirectory = folder
        }
    }

    header: RowLayout {
        id: topRow

        Button {
            id: button

            text: qsTr("Open Directory")

            onClicked: openDirDialog.open()
        }
    }

    ScrollView {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom:  parent.bottom
        id: scrollView

        width: 300

        ListView {
            id: sidelist
            anchors.fill: parent
            model: PhotoDirModel {

            }


            delegate: ItemDelegate {
                width: parent.width



                Rectangle {
                    width: messageText.implicitWidth + 24
                    height: messageText.implicitHeight + 24
                    color: "lightgrey"

                    Label {
                        id: messageText
                        text: model.filename
                        color: "black"
                        anchors.fill: parent
                        anchors.margins: 12
                        wrapMode: Label.Wrap

                    }
                }
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
}

