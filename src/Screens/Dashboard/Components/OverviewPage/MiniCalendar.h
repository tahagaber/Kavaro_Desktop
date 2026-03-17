#pragma once
#include <QFrame>
#include <QDate>

class QLabel;
class QGridLayout;

class MiniCalendar : public QFrame {
    Q_OBJECT
public:
    explicit MiniCalendar(QWidget* parent = nullptr);

private slots:
    void updateCalendar();
    void nextMonth();
    void prevMonth();

private:
    QDate currentDisplayDate;
    QLabel* monthLabel;
    QGridLayout* daysGrid;
};
