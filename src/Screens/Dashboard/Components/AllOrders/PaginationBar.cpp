#include "PaginationBar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

PaginationBar::PaginationBar(QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    infoLabel = new QLabel("Showing 1 to 4 of 1,284 results");
    infoLabel->setStyleSheet("color: #94a3b8; font-size: 13px; font-weight: bold;");
    layout->addWidget(infoLabel);
    
    layout->addStretch();
    
    auto* prevBtn = new QPushButton("Previous");
    prevBtn->setStyleSheet("QPushButton { background-color: #1e2433; color: #94a3b8; border-radius: 6px; padding: 8px 15px; font-weight: bold; } QPushButton:hover { background-color: #2a374a; color: white; }");
    prevBtn->setCursor(Qt::PointingHandCursor);
    layout->addWidget(prevBtn);
    
    // Page buttons
    QStringList pages = {"1", "2", "3", "...", "321"};
    for (int i = 0; i < pages.size(); ++i) {
        auto* btn = new QPushButton(pages[i]);
        btn->setFixedSize(36, 36);
        btn->setCursor(Qt::PointingHandCursor);
        
        if (i == 0) { // Active page
            btn->setStyleSheet("QPushButton { background-color: #3b82f6; color: white; border-radius: 6px; font-weight: bold; font-size: 13px; }");
        } else if (pages[i] == "...") {
            btn->setStyleSheet("QPushButton { background: transparent; color: #94a3b8; border: none; font-weight: bold; font-size: 13px; }");
            btn->setCursor(Qt::ArrowCursor);
        } else {
            btn->setStyleSheet("QPushButton { background: transparent; color: #e2e8f0; border: none; border-radius: 6px; font-weight: bold; font-size: 13px; } QPushButton:hover { background-color: #1e2433; }");
        }
        layout->addWidget(btn);
    }
    
    auto* nextBtn = new QPushButton("Next");
    nextBtn->setStyleSheet("QPushButton { background-color: #1e2433; color: #94a3b8; border-radius: 6px; padding: 8px 15px; font-weight: bold; } QPushButton:hover { background-color: #2a374a; color: white; }");
    nextBtn->setCursor(Qt::PointingHandCursor);
    layout->addWidget(nextBtn);
}
