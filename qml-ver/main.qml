import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import com.graycatworkshop.Arcimboldo 1.0 as Ao

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1600
    height: 900
    title: qsTr("Arcimboldo")

    property Ao.AppStateAccess state: Ao.AppStateAccess{}

    Ao.TargetDirectoryGenerator {
        id: tdg
        currentDirectory: mainWindow.state.currentDirectory
    }

    FileDialog {
        id: openDirDialog
        title: "Choose dir"
        folder: shortcuts.home

        selectFolder: true
        onAccepted: {
            console.log("folder is now: " + folder)
            mainWindow.state.currentDirectory = folder
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

        TextField {
            id: boxCurrentDirInfo

            width: 300

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 11
            text: mainWindow.state.currentDirectory
            onAccepted: {
                mainWindow.state.currentDirectory = text
            }

            validator: Ao.DirectoryPathValidator {}
            color: acceptableInput ? "black" : "red"
        }

        Button {
            id: buttonCopySelection
            width: 150
            text: qsTr("Copy Selection")
            onClicked: sidelist.model.emitCurrentSelection()
        }

        TextField {
            id: boxTargetDirectoryInfo
            width: 300
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 11
            text: tdg.targetDirectory
        }
    }

    Rectangle {
        id: rectangle
        anchors.top: topRow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.margins: 6

        ListView {
            id: sidelist
            width: 300
            boundsBehavior: Flickable.StopAtBounds
            spacing: 3
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            model: Ao.PhotoDirModel {
                currentDirectory: mainWindow.state.currentDirectory
                targetDirectory: tdg.targetDirectory
            }
            delegate: ItemDelegate {
                id: sidelistItemDelegate
                width: parent.width * 0.9
                property string image_url: "file:" + list_item_internal.photo_file_path
                PhotoListItem {
                    id: list_item_internal
                    anchors.fill: parent
                    photo_file_name: model.filename
                    photo_file_path: model.filepath
                    photo_selected: model.selected
                    onItemClicked: {
                        sidelist.currentIndex = index
                    }
                    onItemMarkToggle: {
                        model.selected = !model.selected
                    }
                }

            }

            ScrollBar.vertical: ScrollBar {}
        }

        Image {
            id: mainImagePreview
            source: sidelist.currentItem.image_url
            fillMode: Image.PreserveAspectFit
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: sidelist.right
            anchors.right: parent.right
        }
    }
}

