import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    id: friendlist
    clip: true
    focus: true
    property int selectedIndex: -1
    signal peerClicked(pk: string)

    Menu {
        id: context_menu
        width: 100

        property string peer_pubkey: ""

        MenuItem {
            text: "连接"
            onTriggered: {
                chatEngine.connectToPeer(context_menu.peer_pubkey)
            }
        }
    }

    Component {
        id: friendListDelegate

        Rectangle {
            id: peeritem
            width: friendlist.width
            height: 60
            border.color: "black"
            color: friendlist.selectedIndex === index?"lightsteelblue":"transparent"
            MouseArea {
                anchors.fill: parent
                // preventStealing: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: (mouse)=> {
                    if (mouse.button === Qt.LeftButton) {
                        console.log("clicked",model.pub_key)
                        friendlist.peerClicked(model.pub_key)
                        friendlist.selectedIndex = index
                    }
                    if (mouse.button === Qt.RightButton) {
                        console.log("peer item right button")
                        context_menu.peer_pubkey = model.pub_key
                        context_menu.popup()
                    }
                }
            }
            RowLayout {
                anchors.fill: parent
                anchors.margins: 8
                Column {
                    Layout.horizontalStretchFactor: 2
                    Layout.fillWidth: true
                    Layout.preferredWidth: 30
                    Text {
                        text: model.name
                        font.bold: true
                    }
                    Text {
                        width: parent.width
                        text: model.pub_key
                        elide: Text.ElideRight
                    }
                }
                // Button {

                //     Layout.horizontalStretchFactor: 1
                //     Layout.fillWidth: true
                //     Layout.preferredWidth: 30
                //     id: bt_delete
                //     text: qsTr("删除")
                //     onClicked: {
                //         dialogtest.open()
                //     }

                // }
            }
        }
    }

    spacing: 4
    model: friendListModel
    delegate: friendListDelegate
}
