import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import qml_enchat

Rectangle {
    color: "#f5f5f5"
    border.color: "#dcdcdc"
    border.width: 1
    radius: 8

    ColumnLayout {
        id: right_area
        anchors.margins: 8
        anchors.fill: parent
        spacing: 2

        //聊天记录
        ChatHistoryListView {
            id: history_area
            Layout.preferredWidth: parent.width
            Layout.verticalStretchFactor: 1
            Layout.fillHeight: true
            Layout.preferredHeight: 100


        }

        //发送消息
        Rectangle {
            id: send_area
            Layout.preferredWidth: parent.width
            Layout.verticalStretchFactor: 1
            Layout.maximumHeight: 150
            Layout.fillHeight: true
            Layout.preferredHeight: 100
            border.color: "#ececec"


            TextEdit {
                id: send_text
                anchors.fill: parent
                anchors.margins: 2

                color: "red"
                font.pointSize: 10
                textFormat: TextEdit.PlainText
                wrapMode: TextEdit.WordWrap
                clip: true
            }


        }
        Button {
            id: btn_send
            Layout.preferredHeight: 30
            Layout.preferredWidth: 110
            Layout.alignment: Qt.AlignRight
            font.pointSize: 10
            text: qsTr("发送")
            MouseArea {
                anchors.fill: parent
                enabled: false
                cursorShape: Qt.PointingHandCursor
            }

            contentItem: Text {
                text: btn_send.text
                font: btn_send.font
                color: "#07c160"

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                color: btn_send.pressed? "#c6c6c6":(btn_send.hovered? "#d2d2d2": "#e9e9e9")
                radius: 4
            }
            // ChatHistoryModel {
            //     id: history
            // }

            onClicked: {
                ChatHistoryModel.add(send_text.text)
                ChatEngine.sendText(44,send_text.text)
            }
        }
    }
}

