#pragma once
#include <QWidget>
#include "SettingsCard.h"

class PreferencesSection : public QWidget {
    Q_OBJECT
public:
    explicit PreferencesSection(QWidget* parent = nullptr);
};
