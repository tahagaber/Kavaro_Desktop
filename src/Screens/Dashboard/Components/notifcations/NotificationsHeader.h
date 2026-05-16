#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class NotificationsHeader : public QWidget {
    Q_OBJECT
public:
    explicit NotificationsHeader(QWidget* parent = nullptr);

signals:
    void markAllAsReadClicked();

private:
    QLabel* titleLabel;
    QLabel* subtitleLabel;
    QPushButton* markReadBtn;
};
