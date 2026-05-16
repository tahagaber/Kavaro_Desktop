#include "STLPagination.h"

STLPagination::STLPagination(int currentPage, int totalPages, QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 40, 0, 0);
    layout->setSpacing(10);
    
    auto* leftSide = new QLabel(QString("PAGE %1 OF %2 — SHOWING %3 OF %4 ITEMS").arg(currentPage).arg(totalPages).arg(4).arg(124));
    leftSide->setStyleSheet("color: #64748b; font-size: 11px; font-weight: bold; text-transform: uppercase;");
    
    auto* rightSide = new QHBoxLayout;
    rightSide->setSpacing(5);
    
    auto createPageBtn = [currentPage](const QString& label, bool active = false) {
        auto* btn = new QPushButton(label);
        btn->setFixedSize(32, 32);
        if (active) {
            btn->setStyleSheet(R"(
                QPushButton {
                    background-color: #3b82f6;
                    color: white;
                    border-radius: 6px;
                    font-size: 12px;
                    font-weight: bold;
                    border: none;
                }
            )");
        } else {
            btn->setStyleSheet(R"(
                QPushButton {
                    background-color: #1e293b;
                    color: #94a3b8;
                    border-radius: 6px;
                    font-size: 12px;
                    font-weight: bold;
                    border: none;
                }
                QPushButton:hover {
                    background-color: #334155;
                }
            )");
        }
        return btn;
    };
    
    rightSide->addWidget(createPageBtn("<"));
    rightSide->addWidget(createPageBtn("1", true));
    rightSide->addWidget(createPageBtn("2"));
    rightSide->addWidget(createPageBtn("3"));
    rightSide->addWidget(createPageBtn(">"));
    
    layout->addWidget(leftSide);
    layout->addStretch();
    layout->addLayout(rightSide);
}
