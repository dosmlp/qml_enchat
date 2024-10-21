import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import qml_enchat

Rectangle {
    border.color: "#ececec"
    // radius: 8

    ListView {
        id: chat_record_view
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8
        clip: true
        property bool datachanged: false

        model: ChatHistoryModel
        delegate: chatRecordDelegate
        Component.onCompleted: positionViewAtEnd()
        Connections {
            target: ChatHistoryModel
            function onDataChanged() {
                // chat_record_view.positionViewAtEnd()
                // chat_record_view.contentY = chat_record_view.contentHeight-chat_record_view.height
                // newmsg.tt = chat_record_view.contentHeight-chat_record_view.height+chat_record_view.originY
                // newmsg.start()
                // console.log(newmsg.tt)
                chat_record_view.datachanged = true
            }
        }
        // onContentYChanged: console.log(contentHeight)
        // onHeightChanged: console.log(height)
        onContentHeightChanged: {
            if (datachanged) {
                // datachanged = false
                newmsg.tt = chat_record_view.contentHeight-chat_record_view.height+chat_record_view.originY
                newmsg.start()

            }

        }


        NumberAnimation {
            id: newmsg
            target: chat_record_view
            property var tt: 1
            property: "contentY"
            duration: 300
            to: tt
            easing.type: Easing.OutQuad
            onFinished: chat_record_view.datachanged = false
        }
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
                //聊天内容
                Rectangle {
                    id: msg_content
                    color: sentByMe ? "lightgrey" : "steelblue"
                    width: label_msg.implicitWidth + 24
                    height: label_msg.implicitHeight + 24
                    radius: 4
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


