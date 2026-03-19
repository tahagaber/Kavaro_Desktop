#pragma once
#include <QWidget>

class QLabel;

class PaginationBar : public QWidget {
    Q_OBJECT
public:
    explicit PaginationBar(QWidget* parent = nullptr);

private:
    QLabel* infoLabel;
};
