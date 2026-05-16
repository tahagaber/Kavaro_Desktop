#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class SettingsPage : public QWidget {
    Q_OBJECT
public:
    explicit SettingsPage(QWidget* parent = nullptr);
};
