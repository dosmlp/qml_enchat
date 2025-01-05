import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QWindowKit


Window {
    id: window
    width: 640
    height: 480
    title: qsTr("Hello World")

    visible: false // We hide it first, so we can move the window to our desired position silently.
    Component.onCompleted: {
        windowAgent.setup(window)
        windowAgent.setTitleBar(title_bar)

        window.visible = true
    }
    WindowAgent {
        id: windowAgent
    }
    Rectangle {
        id: title_bar
        color: window.active ? "#f3f3f3" : "#f3f3f3"
        width: parent.width
        height: 30
        Button {
            id: btn_close
            anchors.right: parent.right
            width: 46;height: 30
            padding: 5
            leftPadding: 13
            rightPadding: 13

            contentItem: Image {
                fillMode: Image.PreserveAspectFit
                source: "qrc:/btn/svg_close"
            }

            background: Rectangle {
                color: btn_close.pressed? "#e14949":(btn_close.hovered? "#ed4c4c": "#f3f3f3")
            }
            onClicked: window.close()
            Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Close,btn_close)
        }
        Button {
            id: btn_max
            anchors.right: btn_close.left
            width: 46;height: 30
            padding: 5
            leftPadding: 13
            rightPadding: 13

            contentItem: Image {
                fillMode: Image.PreserveAspectFit
                source: window.visibility === Window.Maximized ? "qrc:/btn/normal":"qrc:/btn/maximized"
            }
            background: Rectangle {
                color: btn_max.pressed? "#dadada":(btn_max.hovered? "#e7e7e7": "#f3f3f3")
            }
            onClicked: {
                if (window.visibility === Window.Maximized) {
                    window.showNormal()
                } else {
                    window.showMaximized()
                }
            }
            Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Maximize,btn_max)
        }
        Button {
            id: btn_minimize
            anchors.right: btn_max.left
            width: 46;height: 30
            padding: 5
            leftPadding: 13
            rightPadding: 13

            contentItem: Image {
                fillMode: Image.PreserveAspectFit
                source: "qrc:/btn/svg_minimize"
            }
            background: Rectangle {
                color: btn_minimize.pressed? "#dadada":(btn_minimize.hovered? "#e7e7e7": "#f3f3f3")
            }
            onClicked: window.showMinimized()
            Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Minimize,btn_minimize)
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 4
        anchors.topMargin: 30

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
