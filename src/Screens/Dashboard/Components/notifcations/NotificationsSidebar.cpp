#include "NotificationsSidebar.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVariant>

NotificationsSidebar::NotificationsSidebar(QWidget* parent) : QWidget(parent) {
    setFixedWidth(240);
    
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 20, 0);
    mainLayout->setSpacing(10);

    // Categories header
    auto* headerLabel = new QLabel("CATEGORIES");
    headerLabel->setStyleSheet("color: #64748b; font-size: 11px; font-weight: bold; letter-spacing: 1px; padding-left: 15px; padding-bottom: 10px;");
    mainLayout->addWidget(headerLabel);

    buttonsLayout = new QVBoxLayout;
    buttonsLayout->setSpacing(5);
    mainLayout->addLayout(buttonsLayout);

    // Create buttons
    buttonsLayout->addWidget(createCategoryButton("📑", "All Events", 24, true));
    buttonsLayout->addWidget(createCategoryButton("⚙️", "Processing", 12));
    buttonsLayout->addWidget(createCategoryButton("💰", "Sales", 4));
    buttonsLayout->addWidget(createCategoryButton("🎛️", "System", 6));
    buttonsLayout->addWidget(createCategoryButton("👥", "Team", 2));

    mainLayout->addStretch();
}

QWidget* NotificationsSidebar::createCategoryButton(const QString& iconText, const QString& titleText, int count, bool isSelected) {
    auto* container = new QWidget(this);
    container->setFixedHeight(45);
    
    auto* layout = new QHBoxLayout(container);
    layout->setContentsMargins(15, 0, 15, 0);

    auto* iconLabel = new QLabel(iconText);
    auto* titleLabel = new QLabel(titleText);
    auto* badgeLabel = new QLabel(QString::number(count));

    badgeLabel->setAlignment(Qt::AlignCenter);

    if (isSelected) {
        container->setStyleSheet(R"(
            QWidget {
                background-color: #1a2235;
                border: 1px solid #2563eb;
                border-radius: 8px;
            }
        )");
        iconLabel->setStyleSheet("color: #60a5fa; border: none; background: transparent;");
        titleLabel->setStyleSheet("color: #60a5fa; font-weight: bold; font-size: 13px; border: none; background: transparent;");
        badgeLabel->setStyleSheet(R"(
            QLabel {
                background-color: #2563eb;
                color: white;
                border: none;
                border-radius: 10px;
                font-size: 11px;
                font-weight: bold;
                padding: 2px 8px;
            }
        )");
        badgeLabel->setFixedHeight(20);
    } else {
        container->setStyleSheet(R"(
            QWidget:hover {
                background-color: #1e293b;
                border-radius: 8px;
            }
        )");
        iconLabel->setStyleSheet("color: #94a3b8; background: transparent;");
        titleLabel->setStyleSheet("color: #cbd5e1; font-size: 13px; font-weight: 500; background: transparent;");
        badgeLabel->setStyleSheet(R"(
            background-color: transparent;
            color: #64748b;
            font-size: 12px;
            font-weight: bold;
        )");
    }

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(badgeLabel);

    return container;
}
