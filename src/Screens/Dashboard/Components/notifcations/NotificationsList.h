#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "NotificationCard.h"

class NotificationsList : public QWidget {
    Q_OBJECT
public:
    explicit NotificationsList(QWidget* parent = nullptr);

private:
    void populateDummyData();
    QVBoxLayout* listLayout;
};
