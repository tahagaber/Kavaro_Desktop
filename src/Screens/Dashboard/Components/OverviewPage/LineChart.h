#pragma once

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QPaintEvent>
#include <QComboBox>
#include <QLabel>

class LineChart : public QWidget {
    Q_OBJECT
public:
    enum ViewMode { Months12, Days30, Days7 };

    explicit LineChart(QWidget* parent = nullptr);
    void setViewMode(ViewMode mode);
    
    // Helper to create the styled period selector for this chart
    QComboBox* createPeriodSelector(QLabel* targetTitleLabel = nullptr);
    
protected:
    void paintEvent(QPaintEvent*) override;
    
private:
    QVector<int> revenueData;
    QVector<int> targetData;
    QStringList labels;
};
