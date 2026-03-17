#pragma once

#include <QMainWindow>
#include <QStackedWidget>

class FinancialDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit FinancialDashboard(QWidget* parent = nullptr);

private:
    QStackedWidget* mainContentStack;
};
