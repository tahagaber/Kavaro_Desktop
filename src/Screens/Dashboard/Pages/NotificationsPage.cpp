#include "NotificationsPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../Components/notifcations/NotificationsHeader.h"
#include "../Components/notifcations/NotificationsSidebar.h"
#include "../Components/notifcations/NotificationsList.h"

NotificationsPage::NotificationsPage(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(30);

    // 1. Header
    auto* header = new NotificationsHeader(this);
    mainLayout->addWidget(header);

    // 2. Content Row
    auto* contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(40);

    auto* sidebar = new NotificationsSidebar(this);
    contentLayout->addWidget(sidebar, 0, Qt::AlignTop);

    auto* list = new NotificationsList(this);
    contentLayout->addWidget(list, 1); // List takes remaining space

    mainLayout->addLayout(contentLayout, 1);
}
