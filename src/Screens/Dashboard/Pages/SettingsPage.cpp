#include "SettingsPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>

#include "../Components/settingsPage/ProfileSection.h"
#include "../Components/settingsPage/PreferencesSection.h"
#include "../Components/settingsPage/SecuritySection.h"
#include "../Components/settingsPage/AccessMetrics.h"

SettingsPage::SettingsPage(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background-color: #0f172a; border: none;");

    auto* container = new QWidget;
    auto* layout = new QVBoxLayout(container);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(30);

    // MAIN CONTENT GRID (2 Columns Top)
    auto* topGrid = new QHBoxLayout();
    topGrid->setSpacing(25);
    
    auto* profile = new ProfileSection(this);
    auto* metrics = new AccessMetrics(this);
    
    topGrid->addWidget(profile, 3);
    topGrid->addWidget(metrics, 1);
    layout->addLayout(topGrid);

    // 2. PREFERENCES
    layout->addWidget(new PreferencesSection(this));

    // 3. SECURITY
    layout->addWidget(new SecuritySection(this));

    layout->addStretch();
    scrollArea->setWidget(container);
    mainLayout->addWidget(scrollArea);
}
