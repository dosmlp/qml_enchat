import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        anchors.margins: 4
        border.color: "#FF0000"

        RowLayout {
            anchors.fill: parent
            anchors.margins: 4

            FriendListView {
                id: peerlistview
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumWidth: 300
            }
            ChatContentView {
                id: ccv
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Component.onCompleted: {
                peerlistview.peerClicked.connect(ccv.test)
            }
        }
    }
}
