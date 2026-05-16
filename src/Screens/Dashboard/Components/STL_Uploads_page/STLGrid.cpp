#include "STLGrid.h"

STLGrid::STLGrid(QWidget* parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(30); // More spacing for modern look
}

void STLGrid::addCard(STLCard* card) {
    layout->addWidget(card, row, col);
    col++;
    if (col >= 3) { // 3 columns for better readability at current widths
        col = 0;
        row++;
    }
}
