#include "NotificationsHeader.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

NotificationsHeader::NotificationsHeader(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Left info
    auto* infoLayout = new QVBoxLayout;
    
    titleLabel = new QLabel("System Activity");
    titleLabel->setStyleSheet("color: white; font-size: 32px; font-weight: bold;");
    
    subtitleLabel = new QLabel("Real-time monitoring of Kavaro Spatial Engine clusters");
    subtitleLabel->setStyleSheet("color: #94a3b8; font-size: 14px;");

    infoLayout->addWidget(titleLabel);
    infoLayout->addWidget(subtitleLabel);

    // Right Action
    markReadBtn = new QPushButton(" ‎ ✔✔ Mark all as read");
    markReadBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #1e293b;
            color: white;
            border: 1px solid #334155;
            border-radius: 8px;
            padding: 10px 20px;
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #334155;
        }
    )");
    connect(markReadBtn, &QPushButton::clicked, this, &NotificationsHeader::markAllAsReadClicked);

    mainLayout->addLayout(infoLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(markReadBtn);
}
