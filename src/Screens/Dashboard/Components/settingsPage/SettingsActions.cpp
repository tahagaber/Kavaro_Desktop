#include "SettingsActions.h"

SettingsActions::SettingsActions(QWidget* parent) : QWidget(parent) {
    auto* actionBar = new QHBoxLayout(this);
    actionBar->setContentsMargins(0, 0, 0, 0);
    actionBar->addStretch();
    
    auto* resetBtn = new QPushButton("Restore Defaults");
    resetBtn->setStyleSheet("color: #94a3b8; font-size: 13px; font-weight: 600; border: none; padding: 10px;");
    
    auto* saveBtn = new QPushButton("Save Preferences");
    saveBtn->setCursor(Qt::PointingHandCursor);
    saveBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #10b981;
            color: white;
            font-weight: 700;
            padding: 12px 40px;
            border-radius: 10px;
        }
        QPushButton:hover { background-color: #059669; }
    )");
    
    actionBar->addWidget(resetBtn);
    actionBar->addSpacing(15);
    actionBar->addWidget(saveBtn);
}
