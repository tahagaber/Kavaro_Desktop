import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: commandCenter
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        ColumnLayout {
            anchors.fill: parent
            spacing: 20

            // Header Section
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true } // spacer
                Text {
                    text: "مركز القيادة الموحد | Command Center"
                    font.pixelSize: 26
                    color: "#ffffff"
                    font.bold: true
                    Layout.alignment: Qt.AlignRight
                }
            }

            // Top Analytics Row (Glassmorphic look)
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                spacing: 20

                Repeater {
                    model: [
                        { title: "إجمالي المبيعات", value: "$420,500", color: "#66fcf1" },
                        { title: "النماذج المنتجة", value: "8,940", color: "#45a29e" },
                        { title: "المستخدمين النشطين", value: "1,240", color: "#00ffcc" },
                        { title: "معدل النمو", value: "+24% 📈", color: "#7289da" }
                    ]
                    
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "#1f2833" // Base dark
                        opacity: 0.9
                        radius: 12
                        border.color: modelData.color
                        border.width: 1

                        // Shadow for depth
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowHorizontalOffset: 0
                            shadowVerticalOffset: 4
                            shadowBlur: 0.8
                            shadowColor: "#000000"
                            shadowOpacity: 0.3
                        }

                        ColumnLayout {
                            anchors.centerIn: parent
                            spacing: 5
                            Text {
                                text: modelData.title
                                color: "#c5c6c7"
                                font.pixelSize: 14
                                Layout.alignment: Qt.AlignHCenter
                            }
                            Text {
                                text: modelData.value
                                color: modelData.color
                                font.pixelSize: 28
                                font.bold: true
                                Layout.alignment: Qt.AlignHCenter
                            }
                        }
                    }
                }
            }

            // Central Area: Charts & System Status
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 20

                // Main Chart Area
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 600
                    Layout.fillHeight: true
                    color: "#1f2833"
                    radius: 12
                    border.color: "#303a45"
                    border.width: 1

                    Text {
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.margins: 15
                        text: "تحليل إنتاج النماذج الثلاثية - شهريا"
                        color: "#ffffff"
                        font.pixelSize: 16
                    }

                    // A placeholder for a complex chart (QChartView in real implementation)
                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width * 0.8
                        height: parent.height * 0.6
                        color: "transparent"
                        border.color: "#c5c6c7"
                        border.width: 1
                        border.dashPattern: [4, 4]
                        
                        Text {
                            anchors.centerIn: parent
                            text: "[ Chart Visualization Space ]"
                            color: "#c5c6c7"
                        }
                    }
                }

                // AI Alerts / Live Status
                Rectangle {
                    Layout.preferredWidth: 350
                    Layout.fillHeight: true
                    color: "#1f2833"
                    radius: 12
                    border.color: "#303a45"
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        
                        Text {
                            text: "تنبيهات النظام الذكية 🧠"
                            color: "#ffffff"
                            font.pixelSize: 16
                            Layout.bottomMargin: 10
                        }

                        ListView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            model: [
                                "⚠️ تحذير: ضغط سيرفر الرندرة يصل لـ 85%",
                                "✅ نجاح: اكتمال معالجة 400 ملف STL جديد",
                                "📈 فرصة: زيادة الطلب على فئة 'ديكورات المنازل'",
                                "🔍 تحليل: انخفاض تفاعل المستخدمين في أوروبا"
                            ]
                            delegate: Rectangle {
                                width: parent.width
                                height: 50
                                color: "#11141a"
                                radius: 8
                                margin: 5
                                
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 10
                                    text: modelData
                                    color: index === 0 ? "#ff4d4d" : (index === 1 ? "#00ffcc" : "#c5c6c7")
                                    font.pixelSize: 13
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
