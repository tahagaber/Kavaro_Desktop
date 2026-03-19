#include "OrderTable.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>

OrderTable::OrderTable(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    table = new QTableWidget(0, 9);
    table->setHorizontalHeaderLabels({"ID", "CLIENT NAME", "PHONE", "ADDRESS", "PRODUCT", "SIZE", "PAINTED", "STATUS", "ACTIONS"});
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch); // Product stretches
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    // Style the table
    table->setStyleSheet(R"(
        QTableWidget {
            background-color: transparent;
            color: #94a3b8;
            border: none;
            outline: none;
            selection-background-color: transparent;
        }
        QHeaderView::section {
            background-color: transparent;
            color: #64748b;
            font-weight: bold;
            font-size: 11px;
            border: none;
            padding: 15px 20px;
        }
        QTableWidget::item {
            border-bottom: 1px solid #1e293b;
            padding: 15px 20px;
            color: #f8fafc;
        }
        QTableWidget::item:selected {
            background-color: transparent;
        }
    )");
    table->setShowGrid(false);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->verticalHeader()->setVisible(false);
    
    // Default column widths
    table->setColumnWidth(0, 40);  // ID
    table->setColumnWidth(1, 170); // Client
    table->setColumnWidth(2, 130); // Phone
    table->setColumnWidth(3, 170); // Address
    table->setColumnWidth(4, 210); // Product (stretches)
    table->setColumnWidth(5, 100);  // Size
    table->setColumnWidth(6, 95);  // Painted
    table->setColumnWidth(7, 150); // Status (Expanded)
    table->setColumnWidth(8, 120); // Actions

    layout->addWidget(table);
}

void OrderTable::updateOrder(const OrderData& updated) {
    for (auto& o : allOrders) {
        if (o.id == updated.id) {
            o = updated;
            break;
        }
    }
    applyFilters("", "Status: All"); // Refresh
}

void OrderTable::deleteOrder(const QString& id) {
    for (int i = 0; i < allOrders.size(); ++i) {
        if (allOrders[i].id == id) {
            allOrders.removeAt(i);
            break;
        }
    }
    applyFilters("", "Status: All"); // Refresh
}

OrderData OrderTable::getOrderDataById(const QString& id) const {
    for (const auto& o : allOrders) {
        if (o.id == id) return o;
    }
    return OrderData();
}

void OrderTable::setOrders(const QList<OrderData>& orders) {
    allOrders = orders;
    applyFilters("", "Status: All");
}

void OrderTable::addOrder(const OrderData& o) {
    allOrders.append(o);
    applyFilters("", "Status: All");
}

void OrderTable::applyFilters(const QString& search, const QString& status) {
    table->setRowCount(0);
    for (const auto& o : allOrders) {
        bool matchesSearch = search.isEmpty() || 
                           o.product.contains(search, Qt::CaseInsensitive) || 
                           o.clientName.contains(search, Qt::CaseInsensitive);
        
        bool matchesStatus = (status == "Status: All") || (o.status == status);

        if (matchesSearch && matchesStatus) {
            int r = table->rowCount();
            table->insertRow(r);
            table->setRowHeight(r, 75); // Taller rows for better spacing
            
            table->setItem(r, 0, createTextItem(o.id));
            table->setItem(r, 1, createTextItem(o.clientName));
            table->setItem(r, 2, createTextItem(o.phone));
            table->setItem(r, 3, createTextItem(o.address));
            table->setItem(r, 4, createTextItem(o.product));
            table->setItem(r, 5, createTextItem(o.sizeStr));
            table->setItem(r, 6, createTextItem(o.isPainted ? "Yes" : "No"));
            table->setCellWidget(r, 7, createStatusPill(o.status));
            table->setCellWidget(r, 8, createActionsWidget(r, o.id));
        }
    }
}

QTableWidgetItem* OrderTable::createTextItem(const QString& text) {
    auto* item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setForeground(QColor("#e2e8f0"));
    return item;
}

QWidget* OrderTable::createStatusPill(const QString& status) {
    auto* w = new QWidget;
    w->setStyleSheet("background: transparent; border: none;");
    auto* lay = new QHBoxLayout(w);
    lay->setContentsMargins(0, 0, 0, 0);
    
    auto* lbl = new QLabel;
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setFixedSize(110, 30);
    
    QString color, bg;
    if (status == "Printing") { color = "#3b82f6"; bg = "rgba(59,130,246,0.15)"; }
    else if (status == "Painting") { color = "#a855f7"; bg = "rgba(168,85,247,0.15)"; }
    else if (status == "Review") { color = "#fbbf24"; bg = "rgba(251,191,36,0.15)"; }
    else if (status == "Delivered") { color = "#22c55e"; bg = "rgba(34,197,94,0.15)"; }
    else if (status == "Returned") { color = "#ef4444"; bg = "rgba(239,68,68,0.15)"; }
    else { color = "#94a3b8"; bg = "rgba(148,163,184,0.15)"; } // Pending
    
    lbl->setText(QString("<span style='color:%1;'>&#9679;</span> %2").arg(color, status));
    lbl->setStyleSheet(QString("background-color: %1; color: %2; border-radius: 15px; font-size: 13px; font-weight: bold;").arg(bg, color));
    
    lay->addWidget(lbl);
    lay->addStretch();
    return w;
}

QWidget* OrderTable::createActionsWidget(int row, const QString& id) {
    auto* w = new QWidget;
    w->setStyleSheet("background: transparent; border: none;");
    auto* lay = new QHBoxLayout(w);
    lay->setContentsMargins(0, 0, 10, 0);
    lay->setSpacing(10);
    
    QString baseStyle = "QPushButton { background: transparent; color: #64748b; border: none; padding: 5px; }";
    
    // Edit Btn
    auto* editBtn = new QPushButton(QString::fromUtf8("\U0001F4DD")); 
    editBtn->setFixedSize(30, 30);
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setToolTip("Edit Order");
    editBtn->setStyleSheet(baseStyle + " QPushButton:hover { color: #3b82f6; }");
    connect(editBtn, &QPushButton::clicked, this, [this, id](){ emit editRequested(id); });

    // Delete Btn
    auto* delBtn = new QPushButton(QString::fromUtf8("\U0001F5D1"));
    delBtn->setFixedSize(30, 30);
    delBtn->setCursor(Qt::PointingHandCursor);
    delBtn->setToolTip("Delete Order");
    delBtn->setStyleSheet(baseStyle + " QPushButton:hover { color: #ef4444; }");
    connect(delBtn, &QPushButton::clicked, this, [this, id](){ emit deleteRequested(id); });
    
    lay->addWidget(editBtn);
    lay->addWidget(delBtn);
    lay->addStretch();
    return w;
}
