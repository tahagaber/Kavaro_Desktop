#pragma once
#include <QWidget>
#include <QLineEdit>
#include "SettingsCard.h"

class ProfileSection : public QWidget {
    Q_OBJECT
public:
    explicit ProfileSection(QWidget* parent = nullptr);
};
