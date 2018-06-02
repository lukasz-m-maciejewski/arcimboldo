import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import com.graycatworkshop.Arcimboldo 1.0 as Ao

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Arcimboldo")


    FileDialog {
        id: openDirDialog
        title: "Choose dir"
        folder: shortcuts.home


        selectFolder: true
        onAccepted: {
            console.log("folder is now: " + folder)
            sidelist.model.currentDirectory = folder
            boxCurrentDirInfo.text = folder
        }
    }

    Row {
        id: topRow

        height: 40

        spacing: 6

        anchors.top: parent.top

        Button {
            id: buttonOpenDir
            width: 150
            text: qsTr("Open Directory")

            onClicked: openDirDialog.open()
        }

        Text {
            id: boxCurrentDirInfo

            width: 300

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 11
            text: "testing 123"

        }

        Button {
            id: buttonCopySelection

            width: 150


            text: qsTr("Copy Selection")

            onClicked: sidelist.model.emitCurrentSelection()
        }
    }

    Rectangle {
        ScrollView {
            id: scrollView

            anchors.left: parent.left
            anchors.top: topRow.bottom
            anchors.bottom:  parent.bottom
            width: 300

            ListView {
                id: sidelist

                anchors.fill: parent
                model: Ao.PhotoDirModel { }
                delegate: ItemDelegate {
                    anchors.left: parent.leftMargin
                    width: parent.width * 0.8

                    PhotoListItem {
                        anchors.fill: parent
                        photo_file_name: model.filename
                        photo_file_path: model.filepath
                        photo_selected: model.selected
                        onItemClicked: {
                            mainImagePreview.source = "file:" + model.filepath
                        }
                        onItemMarkToggle: {
                            model.selected = !model.selected
                        }

                    }
                }
            }
        }

        Image {
            id: mainImagePreview
            fillMode: Image.PreserveAspectFit
            anchors.top: topRow.bottom
            anchors.bottom: parent.bottom
            anchors.left: scrollView.right
            anchors.right: parent.right
        }
    }
}

