#include "AllOrdersPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

AllOrdersPage::AllOrdersPage(QWidget* parent) : QWidget(parent) {
    auto* allOrdersLayout = new QVBoxLayout(this);
    allOrdersLayout->setContentsMargins(40, 40, 40, 40);

    auto* ordersTitle = new QLabel("Global Order Management");
    ordersTitle->setStyleSheet("color: white; font-size: 28px; font-weight: bold; margin-bottom: 10px;");
    allOrdersLayout->addWidget(ordersTitle);

    auto* fullTable = new QTableWidget(12, 6);
    fullTable->setHorizontalHeaderLabels({"ORDER ID", "CLIENT", "STATUS", "VALUE", "PRIORITY", "ACTIONS"});
    fullTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    fullTable->setStyleSheet(R"(
        QTableWidget {
            background-color: transparent;
            border: none;
            gridline-color: #334155;
            color: #94a3b8;
            outline: none;
            background-color: #1e293b; 
            border-radius: 12px;
        }
        QHeaderView::section {
            background-color: transparent;
            color: #64748b;
            padding: 10px;
            border: none;
            font-size: 11px;
            font-weight: 600;
        }
        QTableWidget::item { padding: 5px; border-bottom: 1px solid #334155; }
        QTableWidget::item:selected { background-color: transparent; }
        QTableWidget::item:hover { background-color: transparent; }
    )");
    
    allOrdersLayout->addWidget(fullTable);
}
