import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Sudoku 1.0

ApplicationWindow {
    id: window
    width: 500
    height: 600
    visible: true
    title: "Sudoku"

    property int selectedRow: -1
    property int selectedCol: -1

    property int elapsedSeconds: 0
    property bool timerRunning: false

    property int hintsUsed: 0
    property int maxHints: 3

    Component.onCompleted: timerRunning = true

    Timer {
        id: gameTimer
        interval: 1000
        repeat: true
        running: timerRunning
        onTriggered: elapsedSeconds += 1
    }

    SudokuController {
        id: sudokuController
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        /* Timer + Hints left */
        Row {
            spacing: 20

            Text {
                id: timerLabel
                font.pixelSize: 20
                text: {
                    let m = Math.floor(elapsedSeconds / 60)
                    let s = elapsedSeconds % 60
                    let mm = m < 10 ? "0" + m : "" + m
                    let ss = s < 10 ? "0" + s : "" + s
                    return mm + ":" + ss
                }
            }

            Text {
                id: hintsLeftLabel
                font.pixelSize: 20
                text: "Hints left: " + Math.max(0, maxHints - hintsUsed)
            }
        }

        Row {
            spacing: 40

            Column {
                spacing: 10

                Button {
                    text: "Easy"
                    onClicked: {
                        sudokuController.generateEasy()
                        elapsedSeconds = 0
                        timerRunning = true
                        hintsUsed = 0
                    }
                }

                Button {
                    text: "Medium"
                    onClicked: {
                        sudokuController.generateMedium()
                        elapsedSeconds = 0
                        timerRunning = true
                        hintsUsed = 0
                    }
                }

                Button {
                    text: "Hard"
                    onClicked: {
                        sudokuController.generateHard()
                        elapsedSeconds = 0
                        timerRunning = true
                        hintsUsed = 0
                    }
                }
            }

            Item {
                width: 9 * 40 + 8 * 1
                height: width

                GridLayout {
                    id: grid
                    anchors.centerIn: parent
                    rows: 9
                    columns: 9
                    rowSpacing: 1
                    columnSpacing: 1

                    Repeater {
                        model: 81

                        Rectangle {
                            width: 40
                            height: 40

                            property int r: Math.floor(index / 9)
                            property int c: index % 9

                            color: (window.selectedRow === r && window.selectedCol === c)
                                   ? "#a0c4ff"
                                   : ((Math.floor(r / 3) + Math.floor(c / 3)) % 2 === 0
                                        ? "#c0c0c0"
                                        : "#ffffff")

                            border.color: "black"
                            border.width: 1

                            Text {
                                id: cellText
                                anchors.centerIn: parent
                                font.pixelSize: 18
                                text: {
                                    sudokuController.revision;
                                    let v = sudokuController.getCell(r, c)
                                    return v === 0 ? "" : v
                                }
                            }

                            TextField {
                                id: editor
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 18
                                inputMethodHints: Qt.ImhDigitsOnly
                                maximumLength: 1
                                visible: false
                                focus: false

                                onEditingFinished: {
                                    if (text === "") {
                                        sudokuController.setCell(r, c, 0)
                                    } else {
                                        let v = parseInt(text)
                                        if (!isNaN(v) && v >= 1 && v <= 9) {
                                            sudokuController.setCell(r, c, v)
                                        }
                                    }

                                    visible = false
                                    cellText.visible = true
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    window.selectedRow = r
                                    window.selectedCol = c

                                    editor.text = cellText.text
                                    editor.visible = true
                                    editor.focus = true
                                    cellText.visible = false
                                }
                            }
                        }
                    }
                }
            }
        }

        /* Buttons under the board */
        RowLayout {
            spacing: 10

            Button {
                text: "Load Puzzle"
                onClicked: {
                    sudokuController.loadPuzzle()
                    elapsedSeconds = 0
                    timerRunning = true
                    hintsUsed = 0
                }
            }

            Button {
                text: "Hint"
                onClicked: {
                    sudokuController.hint()
                    hintsUsed += 1

                    if (hintsUsed > maxHints) {
                        timerRunning = false
                    }
                }
            }

            Button {
                text: "Solve"
                onClicked: {
                    sudokuController.solve()
                    timerRunning = false
                }
            }

            Button {
                text: "Check"
                onClicked: {
                    sudokuController.checkSolved()
                    timerRunning = false
                }
            }
        }
    }

    Dialog {
        id: messageDialog
        title: "Message"
        modal: true
        standardButtons: Dialog.NoButton

        Column {
            spacing: 12
            padding: 12

            Text {
                id: dialogText
                text: ""
                wrapMode: Text.WordWrap
            }

            Button {
                text: "Close"
                onClicked: messageDialog.close()
            }
        }
    }

    Connections {
        target: sudokuController

        function onInvalidInput(message) {
            dialogText.text = message
            messageDialog.open()
        }
    }
}
