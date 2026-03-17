#include "Sidebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QPropertyAnimation>

Sidebar::Sidebar(QWidget* parent) : QFrame(parent) {
    setMinimumWidth(220);
    setMaximumWidth(220);
    setStyleSheet("background-color: #0f172a; border-right: 1px solid #1e293b;");
    
    auto* sidebarLayout = new QVBoxLayout(this);
    sidebarLayout->setContentsMargins(0, 20, 0, 0);
    sidebarLayout->setSpacing(5);
    
    QStringList tabNames = {"  📊  Overview", "  📦  All Orders", "  📄  STL Uploads", "  💰  Revenue Analytics", "  🔥  Burn Rate"};
    sidebarGroup = new QButtonGroup(this);
    sidebarGroup->setExclusive(true);

    for(int i = 0; i < tabNames.size(); i++) {
        auto* tab = new QPushButton(tabNames[i]);
        tab->setCheckable(true);
        tab->setChecked(i == 0);
        tab->setStyleSheet(R"(
            QPushButton {
                text-align: left;
                background: transparent;
                color: #94a3b8;
                border: none;
                border-left: 3px solid transparent;
                padding: 15px 20px;
                font-size: 14px;
            }
            QPushButton:hover {
                background-color: #1e293b;
                color: #f8fafc;
            }
            QPushButton:checked {
                color: #3b82f6;
                background-color: #1e293b;
                border-left: 3px solid #3b82f6;
                font-weight: bold;
            }
        )");
        sidebarLayout->addWidget(tab);
        sidebarGroup->addButton(tab, i);
    }
    sidebarLayout->addStretch();
    
    connect(sidebarGroup, &QButtonGroup::idClicked, this, &Sidebar::pageSelected);
}

void Sidebar::toggleExpanded() {
    QPropertyAnimation *minAnim = new QPropertyAnimation(this, "minimumWidth");
    QPropertyAnimation *maxAnim = new QPropertyAnimation(this, "maximumWidth");
    
    int start = isSidebarVisible ? 220 : 0;
    int end = isSidebarVisible ? 0 : 220;
    
    minAnim->setStartValue(start);
    minAnim->setEndValue(end);
    minAnim->setDuration(250);
    minAnim->setEasingCurve(QEasingCurve::InOutQuad);
    
    maxAnim->setStartValue(start);
    maxAnim->setEndValue(end);
    maxAnim->setDuration(250);
    maxAnim->setEasingCurve(QEasingCurve::InOutQuad);
    
    maxAnim->start(QAbstractAnimation::DeleteWhenStopped);
    minAnim->start(QAbstractAnimation::DeleteWhenStopped);
    
    isSidebarVisible = !isSidebarVisible;
}
