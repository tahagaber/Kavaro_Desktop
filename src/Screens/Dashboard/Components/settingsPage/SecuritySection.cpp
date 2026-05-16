#include "SecuritySection.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

SecuritySection::SecuritySection(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* card = new SettingsCard("Security Settings", this);
    auto* content = new QVBoxLayout();
    content->setSpacing(15);

    auto addSecurityRow = [&](const QString& icon, const QString& title, const QString& desc, const QString& btnText, bool danger = false) {
        auto* row = new QHBoxLayout();
        row->setContentsMargins(10, 10, 10, 10);

        // Icon Box
        auto* iconBox = new QLabel(icon);
        iconBox->setFixedSize(50, 50);
        iconBox->setAlignment(Qt::AlignCenter);
        iconBox->setStyleSheet("background-color: #0b0f19; border: 1px solid #1e293b; border-radius: 12px; font-size: 18px;");
        row->addWidget(iconBox);
        row->addSpacing(15);

        // Text
        auto* txtLayout = new QVBoxLayout();
        auto* t = new QLabel(title);
        t->setStyleSheet("color: #f1f5f9; font-size: 14px; font-weight: 700;");
        auto* d = new QLabel(desc);
        d->setStyleSheet("color: #64748b; font-size: 12px; font-weight: 500;");
        txtLayout->addWidget(t);
        txtLayout->addWidget(d);
        row->addLayout(txtLayout);
        row->addStretch();

        // Button
        auto* btn = new QPushButton(btnText);
        btn->setCursor(Qt::PointingHandCursor);
        QString btnStyle = R"(
            QPushButton {
                background-color: #0b0f19;
                border: 1px solid #1e293b;
                color: )" + QString(danger ? "#ef4444" : "#f1f5f9") + R"(;
                font-size: 11px;
                font-weight: 800;
                padding: 12px 24px;
                border-radius: 12px;
            }
            QPushButton:hover { background-color: #1e293b; border-color: #3b82f6; }
        )";
        btn->setStyleSheet(btnStyle);
        row->addWidget(btn);

        content->addLayout(row);
        
        // auto* line = new QFrame(); // Optional divider
        // line->setFixedHeight(1);
        // line->setStyleSheet("background-color: #1e293b;");
        // content->addWidget(line); // Optional
    };

    addSecurityRow("*** ", "Password Management", "Update your system security credentials", "UPDATE");

    card->setContent(content);
    mainLayout->addWidget(card);
}
