#pragma once
#include <QWidget>
#include <QVector>

class StatusBarChart : public QWidget {
    Q_OBJECT
public:
    explicit StatusBarChart(QWidget* parent = nullptr);
    void setData(int delivered, int pending, int returned);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int m_delivered = 65;
    int m_pending = 25;
    int m_returned = 10;
};
