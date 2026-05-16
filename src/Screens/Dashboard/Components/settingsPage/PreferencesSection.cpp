#include "PreferencesSection.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

PreferencesSection::PreferencesSection(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* card = new SettingsCard("Application Preferences", this);
    auto* contentLayout = new QVBoxLayout();
    contentLayout->setSpacing(25);

    QString style = R"(
        QComboBox {
            background-color: #0b0f19;
            border: 1px solid #1e293b;
            border-radius: 12px;
            padding: 12px 16px;
            color: #f1f5f9;
            min-width: 250px;
        }
        QComboBox::drop-down { border: none; }
        QComboBox:hover { border-color: #3b82f6; }
        
        QCheckBox { color: #f1f5f9; font-size: 13px; spacing: 15px; font-weight: 500; }
        QCheckBox::indicator { width: 24px; height: 24px; border-radius: 8px; border: 2px solid #1e293b; background: #0b0f19; }
        QCheckBox::indicator:checked { background: #3b82f6; border-color: #3b82f6; }
        
        QLabel { color: #94a3b8; font-size: 13px; font-weight: 600; background: transparent; border: none; }
    )";

    // Language
    auto* langRow = new QHBoxLayout();
    auto* langLabel = new QLabel("System Language");
    auto* langCombo = new QComboBox();
    langCombo->addItems({"English (US)", "Arabic"});
    langCombo->setStyleSheet(style);
    langRow->addWidget(langLabel);
    langRow->addStretch();
    langRow->addWidget(langCombo);
    contentLayout->addLayout(langRow);

    // Toggles
    auto* renderingCheck = new QCheckBox("Enable Hardware Acceleration");
    renderingCheck->setChecked(true);
    renderingCheck->setStyleSheet(style);
    contentLayout->addWidget(renderingCheck);

    card->setContent(contentLayout);
    mainLayout->addWidget(card);
}
