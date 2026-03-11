import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 500
    height: 600
    visible: true
    title: "Sudoku"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        GridLayout {
            columns: 9
            rowSpacing: 2
            columnSpacing: 2

            Repeater {
                model: sudokuController.board.length

                delegate: Rectangle {
                    width: 40
                    height: 40
                    border.width: 1
                    color: "#ffffff"

                    TextField {
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: sudokuController.board[index]
                        font.pixelSize: 20
                        inputMethodHints: Qt.ImhDigitsOnly

                        onTextChanged: {
                            let r = Math.floor(index / 9)
                            let c = index % 9
                            let v = parseInt(text)
                            if (!isNaN(v))
                                sudokuController.setCell(r, c, v)
                        }
                    }
                }
            }
        }

        Button {
            text: "Reset"
            onClicked: sudokuController.reset()
        }
    }
}
