#include "TopNavbar.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

TopNavbar::TopNavbar(QWidget* parent) : QFrame(parent) {
    setFixedHeight(70);
    setStyleSheet(R"(
        QFrame {
            background-color: #0f172a;
            border-bottom: 1px solid #1e293b;
        }
    )");
    
    auto* navLayout = new QHBoxLayout(this);
    navLayout->setContentsMargins(40, 0, 40, 0);
    navLayout->setSpacing(12);
    
    // Logo
    auto* logo = new QLabel("◆ KAVARO");
    logo->setStyleSheet(R"(
        QLabel {
            color: #ffffff; 
            font-size: 18px; 
            font-weight: 800;
            letter-spacing: 3px;
            margin-right: 20px;
        }
    )");
    navLayout->addWidget(logo);
    
    // Nav buttons
    QStringList navItems = {"Command Center", "Model Lab", "Analytics", "Finance Studio"};
    for(const auto& item : navItems) {
        auto* btn = new QPushButton(item);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setCheckable(true);
        btn->setChecked(item == "Command Center");
        btn->setStyleSheet(R"(
            QPushButton {
                background: transparent;
                color: #94a3b8;
                border: none;
                padding: 10px 18px;
                font-size: 14px;
                font-weight: 600;
                border-radius: 8px;
            }
            QPushButton:hover {
                color: #f8fafc;
            }
            QPushButton:checked {
                color: #3b82f6;
            }
        )");
        navLayout->addWidget(btn);
    }
    
    navLayout->addStretch();
    
    // Search
    auto* search = new QLineEdit;
    search->setPlaceholderText("Search systems...");
    search->setFixedWidth(300);
    search->setStyleSheet(R"(
        QLineEdit {
            background-color: #111827;
            border: 1px solid #1e293b;
            border-radius: 12px;
            padding: 10px 16px;
            color: #f8fafc;
            font-size: 13px;
        }
        QLineEdit:focus {
            border: 1px solid #3b82f6;
            background-color: #030712;
        }
    )");
    navLayout->addWidget(search);
    navLayout->addSpacing(25);
    
    // User profile
    auto* userBtn = new QPushButton("Admin");
    userBtn->setCursor(Qt::PointingHandCursor);
    userBtn->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #3b82f6, stop:1 #2563eb);
            color: white;
            font-weight: 700;
            border-radius: 12px;
            padding: 10px 24px;
            font-size: 13px;
            border: none;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #60a5fa, stop:1 #3b82f6);
        }
    )");
    navLayout->addWidget(userBtn);
}
