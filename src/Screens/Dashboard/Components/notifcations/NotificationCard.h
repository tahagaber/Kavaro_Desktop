#pragma once

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

enum class NotificationType {
    Success,
    Info,
    Error
};

struct NotificationData {
    NotificationType type;
    QString title;
    QString description;
    QString timeAgo;
    QString primaryTag;
    QString secondaryTag;
};

class NotificationCard : public QWidget {
    Q_OBJECT
public:
    explicit NotificationCard(const NotificationData& data, QWidget* parent = nullptr);

private:
    NotificationData m_data;
    QString getBorderColor() const;
    QString getIconColor() const;
    QString getIconStr() const;
};
