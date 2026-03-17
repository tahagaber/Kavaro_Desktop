#include "TopNavbar.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

TopNavbar::TopNavbar(QWidget* parent) : QFrame(parent) {
    setFixedHeight(70);
    setStyleSheet(R"(
        QFrame {
            background-color: #0b1120;
            border-bottom: 1px solid #1e293b;
        }
    )");
    
    auto* navLayout = new QHBoxLayout(this);
    navLayout->setContentsMargins(30, 0, 30, 0);
    navLayout->setSpacing(10);
    
    // Sidebar toggle (Hamburger)
    auto* toggleBtn = new QPushButton("☰");
    toggleBtn->setCursor(Qt::PointingHandCursor);
    toggleBtn->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            color: #94a3b8;
            font-size: 20px;
            border: none;
            padding: 5px;
            border-radius: 4px;
        }
        QPushButton:hover {
            color: #f8fafc;
            background-color: #1e293b;
        }
    )");
    navLayout->addWidget(toggleBtn);
    navLayout->addSpacing(15);

    connect(toggleBtn, &QPushButton::clicked, this, &TopNavbar::toggleSidebarClicked);
    
    // Logo
    auto* logo = new QLabel("◆ KAVARO");
    logo->setStyleSheet(R"(
        color: #ffffff; 
        font-size: 20px; 
        font-weight: 900;
        letter-spacing: 2px;
    )");
    navLayout->addWidget(logo);
    navLayout->addSpacing(40);
    
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
                background-color: rgba(255, 255, 255, 0.05);
            }
            QPushButton:checked {
                background-color: rgba(59, 130, 246, 0.15);
                color: #3b82f6;
                border: 1px solid rgba(59, 130, 246, 0.3);
            }
        )");
        navLayout->addWidget(btn);
    }
    
    navLayout->addStretch();
    
    // Search
    auto* search = new QLineEdit;
    search->setPlaceholderText("🔍 Search Kavaro systems...");
    search->setFixedWidth(280);
    search->setStyleSheet(R"(
        QLineEdit {
            background-color: #1e293b;
            border: 1px solid #334155;
            border-radius: 8px;
            padding: 8px 15px;
            color: #f8fafc;
            font-size: 13px;
        }
        QLineEdit:focus {
            border: 1px solid #3b82f6;
        }
    )");
    navLayout->addWidget(search);
    navLayout->addSpacing(20);
    
    // User profile
    auto* userBtn = new QPushButton("Admin");
    userBtn->setCursor(Qt::PointingHandCursor);
    userBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #e2e8f0;
            color: #0f172a;
            font-weight: bold;
            border-radius: 16px;
            padding: 6px 20px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #ffffff;
        }
    )");
    navLayout->addWidget(userBtn);
}
