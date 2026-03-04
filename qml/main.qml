import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "Dashboard" as Dashboard

Window {
    id: mainWindow
    width: 1440
    height: 900
    visible: true
    title: qsTr("Kavaro Desktop - غرفة العمليات")
    color: "#0b0c10" // Dark theme background

    // Main Layout - Sidebar & Central Content
    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar (SaaS Navigation)
        Rectangle {
            id: sidebar
            Layout.preferredWidth: 260
            Layout.fillHeight: true
            color: "#1f2833" // Slightly lighter dark tone
            radius: 8

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                // Logo/Header Area
                Text {
                    text: "Kavaro"
                    color: "#66fcf1" // Modern neon tone for identity
                    font.pixelSize: 28
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: 30
                }

                // Nav Items
                Repeater {
                    model: [
                        "1️⃣ مركز القيادة",
                        "2️⃣ وحدة ذكاء النماذج",
                        "3️⃣ مختبر سلوك المستخدمين",
                        "4️⃣ استوديو التحليل المالي",
                        "5️⃣ شاشة العمليات المباشرة",
                        "6️⃣ لوحة التحكم الشاملة"
                    ]
                    delegate: Rectangle {
                        width: sidebar.width - 40
                        height: 45
                        color: index === 0 ? "#45a29e" : "transparent"
                        radius: 5
                        
                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: index === 0 ? "#ffffff" : "#c5c6c7"
                            font.pixelSize: 14
                            font.family: "Arial"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // In complete version, handle view switching
                                console.log("Navigating to: " + modelData)
                            }
                        }
                    }
                }

                Item { Layout.fillHeight: true } // spacer
                
                // User Profile Bottom Widget
                Rectangle {
                    width: sidebar.width - 40
                    height: 50
                    color: "#151920"
                    radius: 12
                    
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        Rectangle {
                            width: 30; height: 30; radius: 15; color: "#66fcf1"
                        }
                        Text { text: "Admin User"; color: "#ffffff"; font.pixelSize: 14 }
                    }
                }
            }
        }

        // Central Content Area
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            StackView {
                id: contentView
                anchors.fill: parent
                anchors.margins: 20
                initialItem: Dashboard.CommandCenter {}
                
                // Smooth transition animations representing modern SaaS
                pushEnter: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: 300
                    }
                }
            }
        }
    }
}
