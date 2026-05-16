#include "STLHeader.h"

STLHeader::STLHeader(QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 20);

    auto* leftSide = new QVBoxLayout;
    
    auto* title = new QLabel("STL Repository");
    title->setStyleSheet("color: #f8fafc; font-size: 32px; font-weight: bold; font-family: 'Outfit', sans-serif;");
    
    auto* status = new QLabel("● LIBRARY STATUS: 124 MODELS SYNCED");
    status->setStyleSheet("color: #22c55e; font-size: 11px; font-weight: bold; letter-spacing: 1px;");
    
    leftSide->addWidget(title);
    leftSide->addWidget(status);
    
    auto* rightSide = new QHBoxLayout;
    rightSide->setSpacing(10);
    
    auto* filterBtn = new QPushButton("Filter");
    filterBtn->setFixedSize(90, 36);
    filterBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #1e293b;
            color: #f1f5f9;
            border: 1px solid #334155;
            border-radius: 6px;
            font-size: 13px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #334155;
        }
    )");
    
    auto* sortBtn = new QPushButton("Sort");
    sortBtn->setFixedSize(90, 36);
    sortBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #1e293b;
            color: #f1f5f9;
            border: 1px solid #334155;
            border-radius: 6px;
            font-size: 13px;
            font-weight: 500;
        }
        QPushButton:hover {
            background-color: #334155;
        }
    )");

    rightSide->addWidget(filterBtn);
    rightSide->addWidget(sortBtn);
    
    layout->addLayout(leftSide);
    layout->addStretch();
    layout->addLayout(rightSide);
}
