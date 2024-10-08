import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    Rectangle {
        anchors.fill: parent
        color: "#008d97"
        border.color: "#000000"
        border.width: 1
        radius: 8

        ColumnLayout {
            anchors.margins: 8
            anchors.fill: parent
            spacing: 2

            ChatHistoryListView {

            }

            Rectangle {
                id: send_area
                Layout.preferredWidth: parent.width
                Layout.verticalStretchFactor: 1
                Layout.maximumHeight: 400
                Layout.fillHeight: true
                Layout.preferredHeight: 100
                color: "#333333"

                RowLayout {
                    anchors.fill: parent
                    TextEdit {
                        id: send_text
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "red"
                        textFormat: TextEdit.PlainText
                        wrapMode: TextEdit.WordWrap
                    }
                    Button {
                        id: btn_send
                        height: 30
                        width: 100
                        text: qsTr("发送")
                    }
                }
            }
        }
    }
}
