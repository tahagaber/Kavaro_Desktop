#pragma once

#include <QFrame>
#include <QString>

class MetricCard : public QFrame {
    Q_OBJECT
public:
    MetricCard(const QString& title, const QString& value, 
               const QString& subtitle, const QString& color,
               QWidget* parent = nullptr);
};
