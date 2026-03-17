#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>

class MiniCalendar;
class StatusBarChart;

class OverviewPage : public QWidget {
    Q_OBJECT
public:
    explicit OverviewPage(QWidget* parent = nullptr);



private:
    QTableWidget* mainTable;
    MiniCalendar* mainCalendar;
    StatusBarChart* mainStatusBarChart;
    QScrollArea* scrollArea;
};
