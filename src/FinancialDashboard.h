#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QFrame>
#include <QVector>
#include <QStringList>
#include <QPaintEvent>
#include <QFont>

// ==================== Custom Chart Widget ====================
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

// ==================== Custom Vertical Bar Chart Widget ====================
class OrderStatusChart : public QFrame {
    Q_OBJECT
public:
    explicit OrderStatusChart(QWidget* parent = nullptr);
    
protected:
    void paintEvent(QPaintEvent*) override;
};

// ==================== Metric Card ====================
class MetricCard : public QFrame {
    Q_OBJECT
public:
    MetricCard(const QString& title, const QString& value, 
               const QString& subtitle, const QString& color,
               QWidget* parent = nullptr);
};

// ==================== AI Insight Item ====================
class InsightItem : public QFrame {
    Q_OBJECT
public:
    InsightItem(const QString& type, const QString& content, 
                QWidget* parent = nullptr);
};

// ==================== Main Window ====================
class FinancialDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit FinancialDashboard(QWidget* parent = nullptr);
};
