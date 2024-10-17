import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    border.color: "#ececec"
    // radius: 8

    ListView {
        id: chat_record_view
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8
        clip: true

        model: chatRecordModel
        delegate: chatRecordDelegate


        Component {
            id:chatRecordDelegate
            Column {
                anchors.right: sentByMe ? chat_record_view.contentItem.right : undefined
                spacing: 1

                readonly property bool sentByMe: model.recipient !== "Me"
                Label {
                    id: sender_name
                    visible: !sentByMe
                    text: model.author
                    font.bold: true
                }
                Rectangle {
                    id: msg_content
                    color: sentByMe ? "lightgrey" : "steelblue"
                    width: label_msg.implicitWidth + 24
                    height: label_msg.implicitHeight + 24
                    Label {
                        id: label_msg
                        anchors.fill: parent
                        anchors.margins: 12

                        text: model.message
                    }
                }
                Label {
                    id: msg_time
                    anchors.right: sentByMe ? parent.right : undefined
                    text: Qt.formatDateTime(model.time, "MM-d hh:mm")
                    color: "#aaaaaa"
                }
            }
        }

    }
}


