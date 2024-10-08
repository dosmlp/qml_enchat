import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    border.color: "#345611"
    border.width: 2
    radius: 8
    Layout.preferredWidth: parent.width
    Layout.verticalStretchFactor: 5
    Layout.fillHeight: true
    Layout.preferredHeight: 100

    ListView {
        id: chat_record_view
        anchors.fill: parent
        spacing: 4


        Component {
            id:chatRecordDelegate
            Column {
                anchors.right: sentByMe ? chat_record_view.contentItem.right : undefined
                spacing: 4

                readonly property bool sentByMe: model.recipient !== "Me"
                Label {
                    id: sender_name
                    text: model.sender_name
                }
                Rectangle {
                    id: msg_content
                    color: sentByMe ? "lightgrey" : "steelblue"
                    Label {
                        anchors.fill: parent
                        anchors.margins: 12

                        text: model.message
                    }
                }
                Label {
                    id: msg_time
                }
            }
        }

        model: chatRecordModel
        delegate: chatRecordDelegate
    }
}


