#include "STLCategoryTabs.h"

STLCategoryTabs::STLCategoryTabs(QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 20);
    layout->setSpacing(25); // More spacing for elegance

    QStringList categories = {"All Models", "Gaming", "Anime", "Office Ornaments"};
    
    for (const auto& cat : categories) {
        auto* btn = new QPushButton(cat);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setProperty("category", cat);
        
        tabs.push_back(btn);
        layout->addWidget(btn);
        
        connect(btn, &QPushButton::clicked, this, &STLCategoryTabs::handleTabClick);
    }
    
    updateTabStyles(tabs[0]); // Default to first tab
    layout->addStretch();
}

void STLCategoryTabs::handleTabClick() {
    auto* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        updateTabStyles(btn);
        emit categorySelected(btn->property("category").toString());
    }
}

void STLCategoryTabs::updateTabStyles(QPushButton* activeTab) {
    QString normalStyle = R"(
        QPushButton {
            background-color: transparent;
            color: #64748b;
            border: none;
            padding: 8px 5px;
            font-size: 15px;
            font-weight: 500;
        }
        QPushButton:hover {
            color: #94a3b8;
        }
    )";
    
    QString activeStyle = R"(
        QPushButton {
            background-color: transparent;
            color: #3b82f6;
            border: none;
            border-bottom: 2px solid #3b82f6;
            padding: 8px 5px;
            font-size: 15px;
            font-weight: 700;
        }
    )";
    
    for (auto* btn : tabs) {
        btn->setStyleSheet(btn == activeTab ? activeStyle : normalStyle);
    }
}
