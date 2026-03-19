#include "AllOrdersPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>

#include "../Components/AllOrders/FilterBar.h"
#include "../Components/AllOrders/OrderTable.h"
#include "../Components/AllOrders/PaginationBar.h"
#include "../Components/AllOrders/AddOrder/AddOrderDialog.h"

AllOrdersPage::AllOrdersPage(QWidget* parent) : QWidget(parent) {
    auto* allOrdersLayout = new QVBoxLayout(this);
    allOrdersLayout->setContentsMargins(40, 40, 40, 40);
    allOrdersLayout->setSpacing(25);

    // 1. Top Filter Bar
    auto* filterBar = new FilterBar;
    allOrdersLayout->addWidget(filterBar);

    // 2. Main Order Table Container
    auto* tableContainer = new QWidget;
    tableContainer->setStyleSheet("background-color: #1a2235; border-radius: 12px; border: 1px solid #283548;"); // Match new theme
    auto* tableLayout = new QVBoxLayout(tableContainer);
    tableLayout->setContentsMargins(5, 5, 5, 5);

    orderTable = new OrderTable;
    
    // Add dummy data matching user's image
    QList<OrderData> mockData = {
        {"1", "Taha Gaber", "01234567890", "Cairo, Egypt", "Spider-Man Figure", "12cm", true, "Delivered"},
        {"2", "Ahmed Ali", "01112223344", "Giza, Egypt", "Iron Man Helmet", "15cm", false, "Printing"},
        {"3", "Mohamed Sayed", "01098765432", "Alexandria, Egypt", "Batman Bust", "10cm", true, "Painting"},
        {"4", "Kareem Hassan", "01555666777", "Mansoura, Egypt", "Custom Gear", "8cm", false, "Review"}
    };
    
    orderTable->setOrders(mockData);
    tableLayout->addWidget(orderTable);

    allOrdersLayout->addWidget(tableContainer, 1);

    // 3. Bottom Pagination Bar
    auto* paginationBar = new PaginationBar;
    allOrdersLayout->addWidget(paginationBar);

    connect(filterBar, &FilterBar::addOrderRequested, this, [this]() {
        AddOrderDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            auto formData = dialog.getFormData();
            OrderData newOrder = {
                QString::number(nextOrderId++),
                formData.clientName,
                formData.phone,
                formData.address,
                formData.product,
                formData.size,
                formData.isPainted,
                formData.status
            };
            orderTable->addOrder(newOrder);
        }
    });

    connect(filterBar, &FilterBar::searchChanged, this, [this, filterBar](const QString& text) {
        orderTable->applyFilters(text, filterBar->currentStatus());
    });

    connect(filterBar, &FilterBar::filterChanged, this, [this, filterBar](const QString& cat, const QString& status) {
        orderTable->applyFilters(filterBar->currentSearch(), status);
    });

    // Handle Edit
    connect(orderTable, &OrderTable::editRequested, this, [this](const QString& id) {
        auto oldData = orderTable->getOrderDataById(id);
        auto* dialog = new AddOrderDialog(this);
        
        OrderFormData form;
        form.clientName = oldData.clientName;
        form.phone = oldData.phone;
        form.address = oldData.address;
        form.product = oldData.product;
        form.size = oldData.sizeStr;
        form.isPainted = oldData.isPainted;
        form.status = oldData.status;
        
        dialog->setFormData(form);

        if (dialog->exec() == QDialog::Accepted) {
            auto updatedForm = dialog->getFormData();
            OrderData updatedData = {
                id,
                updatedForm.clientName,
                updatedForm.phone,
                updatedForm.address,
                updatedForm.product,
                updatedForm.size,
                updatedForm.isPainted,
                updatedForm.status
            };
            orderTable->updateOrder(updatedData);
        }
    });

    // Handle Delete
    connect(orderTable, &OrderTable::deleteRequested, this, [this](const QString& id) {
        auto* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Confirm Delete");
        msgBox->setText("Are you sure you want to permanentely delete this order?");
        msgBox->setInformativeText("This action cannot be undone.");
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox->setDefaultButton(QMessageBox::No);
        
        // Premium Dark Style for MessageBox
        msgBox->setStyleSheet(R"(
            QMessageBox { background-color: #0f172a; border: 1px solid #1e293b; border-radius: 12px; }
            QLabel { color: #f8fafc; font-size: 14px; }
            QPushButton { 
                background-color: #1e293b; color: #94a3b8; padding: 8px 16px; 
                border-radius: 6px; font-weight: bold; min-width: 80px; 
            }
            QPushButton:hover { background-color: #334155; color: white; }
            QPushButton[text="&Yes"] { background-color: #ef4444; color: white; }
            QPushButton[text="&Yes"]:hover { background-color: #dc2626; }
        )");

        if (msgBox->exec() == QMessageBox::Yes) {
            orderTable->deleteOrder(id);
        }
    });
}
