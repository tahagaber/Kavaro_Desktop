#pragma once

#include <QFrame>
#include <QPaintEvent>

class OrderStatusChart : public QFrame {
    Q_OBJECT
public:
    explicit OrderStatusChart(QWidget* parent = nullptr);
    void updateData(int completed, int printing, int returned);
    
protected:
    void paintEvent(QPaintEvent*) override;

private:
    int m_completed = 2450;
    int m_pending = 850;
    int m_returned = 120;
};
