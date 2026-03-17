#pragma once

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPaintEvent>

class LineChart : public QWidget {
    Q_OBJECT
public:
    enum ViewMode { Months12, Days30, Days7 };

    explicit LineChart(QWidget* parent = nullptr);
    void setViewMode(ViewMode mode);
    
protected:
    void paintEvent(QPaintEvent*) override;
    
private:
    QVector<int> revenueData;
    QVector<int> targetData;
    QStringList labels;
};
