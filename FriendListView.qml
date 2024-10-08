import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

ListView {
    id: friendlist
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
                    Text {
                        text: model.name
                        font.bold: true
                    }
                    Text {
                        text: model.pub_key
                    }
                }
                Button {

                    Layout.horizontalStretchFactor: 1
                    Layout.fillWidth: true
                    id: bt_delete
                    text: qsTr("删除")
                    onClicked: c_delete.open()

                }
            }



        }
    }

    spacing: 4
    model: friendListModel
    delegate: friendListDelegate
}
