import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

ListView {
    id: friendlist
    clip: true

    FluContentDialog {
        id: c_delete
        title: qsTr("提示")
        message: qsTr("删除此条记录？")
    }

    Component {
        id: friendListDelegate
        Rectangle {
            width: friendlist.width
            height: 60
            border.color: "black"
            MouseArea {
                anchors.fill: parent
                preventStealing: true
                onClicked: (mouse)=> {
                    if ((mouse.button == Qt.LeftButton))
                        console.log(model.name)
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
