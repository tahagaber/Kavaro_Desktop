#pragma once
#include <QWidget>
#include <QGridLayout>
#include "STLCard.h"

class STLGrid : public QWidget {
    Q_OBJECT
public:
    explicit STLGrid(QWidget* parent = nullptr);
    void addCard(STLCard* card);
private:
    QGridLayout* layout;
    int row = 0;
    int col = 0;
};
