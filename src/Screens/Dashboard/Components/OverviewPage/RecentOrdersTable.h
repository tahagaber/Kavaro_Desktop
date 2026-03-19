#pragma once

#include <QFrame>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QMenu>
#include <QAction>

class RecentOrdersTable : public QFrame {
    Q_OBJECT

public:
    explicit RecentOrdersTable(QWidget* parent = nullptr);

private:
    void setupTable();
    void populateSampleData();
    void updateStatusUI(QLabel* statusLabel, int row, const QString& text);

    QTableWidget* mainTable;
};
