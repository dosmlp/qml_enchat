import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        x: 4;y: 4
        width: parent.width-8
        height: parent.height-8
        RowLayout {
            anchors.fill: parent

            FriendListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumWidth: 300
            }
            ChatContentView {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
