import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.4
import "Constants.js" as Constants

ApplicationWindow {
    id: window

    objectName: "mainWindow"
    title: "App"

    FontLoader {
        id: monoFont

        source: "qrc:/fonts/RobotoMono-Medium.ttf"
    }

    Column {
        Text {
            font.family: monoFont
            text: "Hello, snuggle!"
        }

        Image {
            source: "qrc:/icons/lonely_face.png"
        }
    }
}
