#pragma once
#include <QWidget>
#include <QString>

class QTableWidget;
class QTableWidgetItem;

struct OrderData {
    QString id;
    QString clientName;
    QString phone;
    QString address;
    QString product;
    QString sizeStr;
    bool isPainted;
    QString status;
};

class OrderTable : public QWidget {
    Q_OBJECT
public:
    explicit OrderTable(QWidget* parent = nullptr);
    void setOrders(const QList<OrderData>& orders);
    void addOrder(const OrderData& o);
    void applyFilters(const QString& search, const QString& status);
    void updateOrder(const OrderData& updated);
    void deleteOrder(const QString& id);
    OrderData getOrderDataById(const QString& id) const;

signals:
    void editRequested(const QString& id);
    void deleteRequested(const QString& id);

private:
    QList<OrderData> allOrders;
    QTableWidget* table;
    QWidget* createStatusPill(const QString& status);
    QWidget* createActionsWidget(int row, const QString& id);
    QTableWidgetItem* createTextItem(const QString& text);
};
