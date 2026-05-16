#include "SettingsPage.h"

SettingsPage::SettingsPage(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    
    auto* label = new QLabel("Settings Page\nManage your application settings.");
    label->setStyleSheet("color: white; font-size: 20px; font-weight: bold; padding: 40px;");
    
    layout->addWidget(label);
    layout->addStretch();
}
