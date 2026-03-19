#pragma once
#include <QWidget>
class OrderTable;

class AllOrdersPage : public QWidget {
    Q_OBJECT
public:
    explicit AllOrdersPage(QWidget* parent = nullptr);

private:
    OrderTable* orderTable;
    int nextOrderId = 5;
};
