#include "OverviewPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QMenu>
#include <QAction>
#include "../Components/OverviewPage/LineChart.h"
#include "../Components/OverviewPage/MiniCalendar.h"
#include "../Components/OverviewPage/StatusBarChart.h"
#include "../Components/OverviewPage/MetricCard.h"

OverviewPage::OverviewPage(QWidget* parent) : QWidget(parent) {
    auto* overviewLayout = new QVBoxLayout(this);
    overviewLayout->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(R"(
        QScrollArea {
            background-color: transparent;
            border: none;
        }
        QScrollBar:vertical {
            border: none;
            background: #0f172a;
            width: 8px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #334155;
            min-height: 20px;
            border-radius: 4px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )");

    auto* contentArea = new QWidget;
    contentArea->setStyleSheet("background-color: transparent;");
    auto* contentLayout = new QHBoxLayout(contentArea);
    contentLayout->setContentsMargins(15, 15, 15, 15);
    contentLayout->setSpacing(15);
    
    // LEFT COLUMN (Charts + Table)
    auto* leftCol = new QWidget;
    auto* leftLayout = new QVBoxLayout(leftCol);
    leftLayout->setSpacing(20);
    
    // --- Metric Cards ---
    auto* cardsRow = new QHBoxLayout;
    cardsRow->setSpacing(10);
    
    cardsRow->addWidget(new MetricCard("TOTAL REVENUE", "$20K",
                                      "↑ +12.5% vs last month", "blue"));
    cardsRow->addWidget(new MetricCard("MONTHLY BURN", "$1.4K",
                                      "↓ -4.2% Optimized", "orange"));
    cardsRow->addWidget(new MetricCard("PORTFOLIO ROI", "+2.8%",
                                      "↑ +3.1% Target exceeded", "green"));
    cardsRow->addWidget(new MetricCard("COMPUTE COST", "$50K",
                                      "→ Stable H100 Clusters", "gray"));
    
    leftLayout->addLayout(cardsRow);
    
    // --- Chart Section ---
    auto* chartCard = new QFrame;
    chartCard->setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
    )");
    
    auto* chartLayout = new QVBoxLayout(chartCard);
    chartLayout->setContentsMargins(20, 20, 20, 20);
    
    // Chart header
    auto* chartHeader = new QHBoxLayout;
    auto* chartTitle = new QLabel("Multi-Currency Growth (USD/EUR/JPY)");
    chartTitle->setStyleSheet("color: #f8fafc; font-size: 16px; font-weight: bold;");
    
    auto* chartSubtitle = new QLabel("Projected scaling vs actual performance");
    chartSubtitle->setStyleSheet("color: #64748b; font-size: 12px;");
    
    auto* titleCol = new QVBoxLayout;
    titleCol->addWidget(chartTitle);
    titleCol->addWidget(chartSubtitle);
    
    chartHeader->addLayout(titleCol);
    chartHeader->addStretch();
    
    // Legend
    auto* legend = new QHBoxLayout;
    
    auto* revPill = new QFrame;
    revPill->setStyleSheet("background-color: #0f172a; border-radius: 6px;");
    auto* revPillLayout = new QHBoxLayout(revPill);
    revPillLayout->setContentsMargins(10, 5, 10, 5);
    auto* revDot = new QLabel("●");
    revDot->setStyleSheet("color: #3b82f6; font-size: 10px;");
    auto* revTxt = new QLabel("Revenue");
    revTxt->setStyleSheet("color: #e2e8f0; font-size: 11px;");
    revPillLayout->addWidget(revDot);
    revPillLayout->addWidget(revTxt);
    
    auto* tgtPill = new QFrame;
    tgtPill->setStyleSheet("background-color: #0f172a; border-radius: 6px;");
    auto* tgtPillLayout = new QHBoxLayout(tgtPill);
    tgtPillLayout->setContentsMargins(10, 5, 10, 5);
    auto* tgtDot = new QLabel("●");
    tgtDot->setStyleSheet("color: #64748b; font-size: 10px;");
    auto* tgtTxt = new QLabel("Target");
    tgtTxt->setStyleSheet("color: #94a3b8; font-size: 11px;");
    tgtPillLayout->addWidget(tgtDot);
    tgtPillLayout->addWidget(tgtTxt);
    
    auto* periodCombo = new QComboBox;
    periodCombo->setCursor(Qt::PointingHandCursor);
    periodCombo->addItems({"Last 12 Months", "Last 30 Days", "Last 7 Days"});
    periodCombo->setStyleSheet(R"(
        QComboBox {
            background-color: #334155;
            color: #94a3b8;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 12px;
            border: none;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: #1e293b;
            color: #f8fafc;
            selection-background-color: #3b82f6;
            border: 1px solid #334155;
            border-radius: 4px;
        }
    )");
    
    legend->addWidget(revPill);
    legend->addWidget(tgtPill);
    legend->addSpacing(20);
    legend->addWidget(periodCombo);
    chartHeader->addLayout(legend);
    
    chartLayout->addLayout(chartHeader);
    
    // Chart widget
    auto* lineChart = new LineChart;
    chartLayout->addWidget(lineChart);
    
    // Connect combo box to update chart
    connect(periodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), [lineChart, chartTitle](int index) {
        if (index == 0) {
            lineChart->setViewMode(LineChart::Months12);
            chartTitle->setText("Multi-Currency Growth (12 Months)");
        } else if (index == 1) {
            lineChart->setViewMode(LineChart::Days30);
            chartTitle->setText("Multi-Currency Growth (30 Days)");
        } else if (index == 2) {
            lineChart->setViewMode(LineChart::Days7);
            chartTitle->setText("Multi-Currency Growth (7 Days)");
        }
    });
    
    leftLayout->addWidget(chartCard, 2);
    
    // --- Transaction Table ---
    auto* tableCard = new QFrame;
    tableCard->setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
        QTableWidget {
            background-color: transparent;
            border: none;
            color: #e2e8f0;
            gridline-color: #334155;
        }
        QHeaderView::section {
            background-color: transparent;
            color: #64748b;
            padding: 10px;
            border: none;
            font-size: 11px;
            font-weight: 600;
        }
        QTableWidget::item {
            padding: 12px;
            border-bottom: 1px solid #334155;
        }
    )");
    
    auto* tableLayout = new QVBoxLayout(tableCard);
    tableLayout->setContentsMargins(20, 20, 20, 20);
    
    auto* tableHeader = new QHBoxLayout;
    auto* tableTitle = new QLabel("Recent 3D Print Orders");
    tableTitle->setStyleSheet("color: #f8fafc; font-size: 16px; font-weight: bold;");
    tableHeader->addWidget(tableTitle);
    tableHeader->addStretch();
    
    auto* exportBtn = new QPushButton("Export CSV");
    exportBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #334155;
            color: #94a3b8;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 12px;
        }
    )");
    tableHeader->addWidget(exportBtn);
    
    auto* filterBtn = new QPushButton("Filter");
    filterBtn->setStyleSheet(exportBtn->styleSheet());
    tableHeader->addWidget(filterBtn);
    
    tableLayout->addLayout(tableHeader);
    
    // Table
    mainTable = new QTableWidget(3, 9);
    mainTable->setHorizontalHeaderLabels(
        QStringList() << "ORDER ID" << "CLIENT NAME" << "ADDRESS" << "3D MODEL" 
                     << "PRINT TYPE" << "PRICE" << "STATUS" << "DATE" << "ACTION");
    mainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    mainTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Stretch address
    mainTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch); // Stretch 3D model column
    mainTable->verticalHeader()->setVisible(false);
    mainTable->setSelectionMode(QAbstractItemView::NoSelection);
    mainTable->setFocusPolicy(Qt::NoFocus);
    mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers); 
    mainTable->verticalHeader()->setDefaultSectionSize(50);
    
    mainTable->setStyleSheet(R"(
        QTableWidget {
            background-color: transparent;
            border: none;
            gridline-color: #334155;
            color: #94a3b8;
            outline: none;
        }
        QTableWidget::item { padding: 5px; }
        QTableWidget::item:selected { background-color: transparent; }
        QTableWidget::item:hover { background-color: transparent; }
    )");
    
    // Sample data
    QStringList ids = {"#PRN-1042", "#PRN-1043", "#PRN-1044"};
    QStringList clients = {"Ahmed Hassan", "Sarah Connor", "Kavaro Studio"};
    QStringList addresses = {"Cairo, Maadi St 42", "Alexandria, 14 Smouha", "Giza, Dokki 10"};
    QStringList models = {"Spider-Man Bust (20cm)", "Darth Vader Helmet", "Custom Gear Assembly"};
    QStringList types = {"Resin (Grey)", "PLA (Black)", "PETG (White)"};
    QStringList prices = {"1,200 EGP", "850 EGP", "4,500 EGP"};
    QStringList initialStatuses = {"Completed", "Printing", "Under Review"};
    QStringList timestamps = {"04 Mar 2026, 14:21", "04 Mar 2026, 13:05", "03 Mar 2026, 11:45"};
    
    // Status options requested by user
    QStringList statusOptions = {"Under Review", "Printing", "Coloring", "Shipping", "Completed", "Returned"};
    
    for(int row = 0; row < 3; row++) {
        mainTable->setItem(row, 0, new QTableWidgetItem(ids[row]));
        mainTable->setItem(row, 1, new QTableWidgetItem(clients[row]));
        mainTable->setItem(row, 2, new QTableWidgetItem(addresses[row]));
        
        auto* modelItem = new QTableWidgetItem(models[row]);
        modelItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        mainTable->setItem(row, 3, modelItem);
        
        mainTable->setItem(row, 4, new QTableWidgetItem(types[row]));
        
        auto* priceItem = new QTableWidgetItem(prices[row]);
        priceItem->setForeground(QColor("#4ade80"));
        priceItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        mainTable->setItem(row, 5, priceItem);
        
        // Setup display-only Status Label
        auto* statusLabel = new QLabel(initialStatuses[row]);
        statusLabel->setAlignment(Qt::AlignCenter);
        
        // Initialize dynamic coloring lambda directly over the label
        auto updateStatusUI = [statusLabel, row, this](const QString& text) {
            statusLabel->setText(" " + text + " ");
            
            // Store the state cleanly in the first column item for easy retrieval
            if (mainTable->item(row, 0)) {
                mainTable->item(row, 0)->setData(Qt::UserRole, text.trimmed());
            }
            
            QString bgColor = "#334155";
            QString textColor = "#f8fafc";
            
            if (text == "Completed") { bgColor = "rgba(34, 197, 94, 0.2)"; textColor = "#4ade80"; } 
            else if (text == "Printing" || text == "Under Review" || text == "Coloring" || text == "Shipping") { bgColor = "rgba(245, 158, 11, 0.2)"; textColor = "#fbbf24"; } 
            else if (text == "Returned") { bgColor = "rgba(239, 68, 68, 0.2)"; textColor = "#f87171"; } 
            
            statusLabel->setStyleSheet(QString(R"(
                QLabel {
                    background-color: %1;
                    color: %2;
                    border: 1px solid %1;
                    border-radius: 6px;
                    padding: 4px;
                    font-weight: bold;
                    font-size: 11px;
                }
            )").arg(bgColor, textColor));
        };
        
        updateStatusUI(initialStatuses[row]);
        
        // Add widget to cell
        auto* labelContainer = new QWidget;
        auto* lcLayout = new QHBoxLayout(labelContainer);
        lcLayout->setContentsMargins(5, 5, 5, 5);
        lcLayout->addWidget(statusLabel);
        mainTable->setCellWidget(row, 6, labelContainer);
        
        mainTable->setItem(row, 7, new QTableWidgetItem(timestamps[row]));
        
        // Add an Action Button
        auto* actionBtn = new QPushButton("⚙️");
        actionBtn->setCursor(Qt::PointingHandCursor);
        actionBtn->setToolTip("Manage Order");
        actionBtn->setStyleSheet(R"(
            QPushButton {
                background: transparent;
                color: #94a3b8;
                border: none;
                font-size: 16px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #334155;
                color: #f8fafc;
            }
        )");
        
        // Add context menu to action button
        auto* menu = new QMenu(actionBtn);
        menu->setStyleSheet("QMenu { background-color: #1e293b; color: #f8fafc; border: 1px solid #334155; } QMenu::item:selected { background-color: #3b82f6; }");
        
        // Create dynamic sub-menu for status updates
        auto* updateMenu = menu->addMenu("⏳ Update Status");
        updateMenu->setStyleSheet(menu->styleSheet());
        
        // Populate the submenu and connect it to update REALTIME
        for (const QString& statusText : statusOptions) {
            QAction* statusAct = updateMenu->addAction(statusText);
            connect(statusAct, &QAction::triggered, [this, updateStatusUI, statusText]() {
                updateStatusUI(statusText);
                // updateOrderStatusChart() removed
            });
        }
        
        menu->addSeparator();
        menu->addAction("📩 Send Invoice");
        menu->addAction("🖨️ Download 3D Model");
        menu->addAction("❌ Cancel Order");
        actionBtn->setMenu(menu);

        mainTable->setCellWidget(row, 8, actionBtn);
    }
    
    tableLayout->addWidget(mainTable);
    leftLayout->addWidget(tableCard, 0); // Remove fixed stretch to let it float better
    
    // --- RIGHT COLUMN ---
    auto* rightCol = new QWidget;
    rightCol->setFixedWidth(310); // Match MiniCalendar width precisely
    auto* rightLayout = new QVBoxLayout(rightCol);
    rightLayout->setSpacing(25);

    // 1. Mini Calendar at the TOP
    mainCalendar = new MiniCalendar;
    rightLayout->addWidget(mainCalendar);

    // 2. Order Status Bar Chart below it (Container fixed at 300x330)
    auto* statsCard = new QFrame;
    statsCard->setFixedSize(300, 330);
    statsCard->setStyleSheet("background-color: #1e293b; border-radius: 12px; border: 1px solid #334155;");
    auto* statsLayout = new QVBoxLayout(statsCard);
    statsLayout->setContentsMargins(0, 0, 0, 0); // Component handles internal margins

    mainStatusBarChart = new StatusBarChart;
    statsLayout->addWidget(mainStatusBarChart);
    
    rightLayout->addWidget(statsCard);
    rightLayout->addStretch();

    // Assemble Overview Page
    contentLayout->addWidget(leftCol, 3);
    contentLayout->addWidget(rightCol, 1);
    
    scrollArea->setWidget(contentArea);
    overviewLayout->addWidget(scrollArea);
    
    // updateOrderStatusChart() removed
}



