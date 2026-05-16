#pragma once
#include <QWidget>
class OrderTable;
class FilterBar;

class AllOrdersPage : public QWidget {
    Q_OBJECT
public:
    explicit AllOrdersPage(QWidget* parent = nullptr);

private:
    void setupUI();
    void setupConnections();
    void loadInitialData();
    void handleAddOrder();
    void handleEditOrder(const QString& id);
    void handleDeleteOrder(const QString& id);

    OrderTable* orderTable;
    FilterBar* filterBar;
    int nextOrderId = 5;
};
