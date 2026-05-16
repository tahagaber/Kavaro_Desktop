#pragma once
#include <QWidget>
#include "SettingsCard.h"

class AccessMetrics : public QWidget {
    Q_OBJECT
public:
    explicit AccessMetrics(QWidget* parent = nullptr);

private slots:
    void updateTime();

private:
    QLabel* m_timeLabel;
    QTimer* m_timer;
};
