#include "RecentOrdersTable.h"

RecentOrdersTable::RecentOrdersTable(QWidget* parent) : QFrame(parent) {
    setStyleSheet(R"(
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

    auto* tableLayout = new QVBoxLayout(this);
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

    setupTable();
    populateSampleData();
    tableLayout->addWidget(mainTable);
}

void RecentOrdersTable::setupTable() {
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
}

void RecentOrdersTable::populateSampleData() {
    QStringList ids = {"#PRN-1042", "#PRN-1043", "#PRN-1044"};
    QStringList clients = {"Ahmed Hassan", "Sarah Connor", "Kavaro Studio"};
    QStringList addresses = {"Cairo, Maadi St 42", "Alexandria, 14 Smouha", "Giza, Dokki 10"};
    QStringList models = {"Spider-Man Bust (20cm)", "Darth Vader Helmet", "Custom Gear Assembly"};
    QStringList types = {"Resin (Grey)", "PLA (Black)", "PETG (White)"};
    QStringList prices = {"1,200 EGP", "850 EGP", "4,500 EGP"};
    QStringList initialStatuses = {"Completed", "Printing", "Under Review"};
    QStringList timestamps = {"04 Mar 2026, 14:21", "04 Mar 2026, 13:05", "03 Mar 2026, 11:45"};
    
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
        
        auto* statusLabel = new QLabel(initialStatuses[row]);
        statusLabel->setAlignment(Qt::AlignCenter);
        
        updateStatusUI(statusLabel, row, initialStatuses[row]);
        
        auto* labelContainer = new QWidget;
        auto* lcLayout = new QHBoxLayout(labelContainer);
        lcLayout->setContentsMargins(5, 5, 5, 5);
        lcLayout->addWidget(statusLabel);
        mainTable->setCellWidget(row, 6, labelContainer);
        
        mainTable->setItem(row, 7, new QTableWidgetItem(timestamps[row]));
        
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
        
        auto* menu = new QMenu(actionBtn);
        menu->setStyleSheet("QMenu { background-color: #1e293b; color: #f8fafc; border: 1px solid #334155; } QMenu::item:selected { background-color: #3b82f6; }");
        
        auto* updateMenu = menu->addMenu("⏳ Update Status");
        updateMenu->setStyleSheet(menu->styleSheet());
        
        for (const QString& statusText : statusOptions) {
            QAction* statusAct = updateMenu->addAction(statusText);
            connect(statusAct, &QAction::triggered, [this, statusLabel, row, statusText]() {
                updateStatusUI(statusLabel, row, statusText);
            });
        }
        
        menu->addSeparator();
        menu->addAction("📩 Send Invoice");
        menu->addAction("🖨️ Download 3D Model");
        menu->addAction("❌ Cancel Order");
        actionBtn->setMenu(menu);

        mainTable->setCellWidget(row, 8, actionBtn);
    }
}

void RecentOrdersTable::updateStatusUI(QLabel* statusLabel, int row, const QString& text) {
    statusLabel->setText(" " + text + " ");
    
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
}
