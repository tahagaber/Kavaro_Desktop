#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>

class MiniCalendar;
class StatusBarChart;
class RecentOrdersTable;

class OverviewPage : public QWidget {
    Q_OBJECT
public:
    explicit OverviewPage(QWidget* parent = nullptr);

private:
    RecentOrdersTable* recentOrdersTable;
    MiniCalendar* mainCalendar;
    StatusBarChart* mainStatusBarChart;
    QScrollArea* scrollArea;
};
