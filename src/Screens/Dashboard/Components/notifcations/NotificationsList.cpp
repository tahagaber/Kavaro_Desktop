#include "NotificationsList.h"

NotificationsList::NotificationsList(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(R"(
        QScrollArea {
            border: none;
            background-color: transparent;
        }
        QScrollBar:vertical {
            background: #0f172a;
            width: 8px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #334155;
            min-height: 20px;
            border-radius: 4px;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )");

    auto* scrollContent = new QWidget(scrollArea);
    scrollContent->setStyleSheet("background-color: transparent;");
    
    listLayout = new QVBoxLayout(scrollContent);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setSpacing(20);

    populateDummyData();

    listLayout->addStretch();
    scrollArea->setWidget(scrollContent);
    
    mainLayout->addWidget(scrollArea);
}

void NotificationsList::populateDummyData() {
    // 1. STL Processed
    NotificationData stlData;
    stlData.type = NotificationType::Success;
    stlData.title = "STL Processed Successfully";
    stlData.timeAgo = "2 MIN AGO";
    stlData.description = "Geometric optimization complete for <span style='color:#60a5fa;'>Model_KV_Alpha.stl</span>. 4.2M polygons simplified to 1.1M without topological loss.";
    stlData.primaryTag = "PROCESSING";
    stlData.secondaryTag = "ID: KV-9821-A";
    listLayout->addWidget(new NotificationCard(stlData));

    // 2. Transaction
    NotificationData transData;
    transData.type = NotificationType::Info;
    transData.title = "New Transaction: $1,250";
    transData.timeAgo = "14 MIN AGO";
    transData.description = "Enterprise tier subscription renewed for <span style='color:#f8fafc; font-weight:bold;'>Zenith Spatial Labs</span>. License valid until Oct 2025.";
    transData.primaryTag = "SALES";
    transData.secondaryTag = "INVOICE: #ZSL-C092";
    listLayout->addWidget(new NotificationCard(transData));

    // 3. User joined
    NotificationData userData;
    userData.type = NotificationType::Info; // We'll reuse Info for blue
    userData.title = "User Alex Rivera joined";
    userData.timeAgo = "1 HOUR AGO";
    userData.description = "Assigned to <span style='color:#f8fafc; font-weight:bold;'>Precision Engineering Group</span> as a Senior Architect.";
    userData.primaryTag = "TEAM";
    userData.secondaryTag = "ACCESS: LEVEL-4";
    listLayout->addWidget(new NotificationCard(userData));

    // 4. Error
    NotificationData errorData;
    errorData.type = NotificationType::Error;
    errorData.title = "Error: STL Mesh Integrity Failure";
    errorData.timeAgo = "3 HOURS AGO";
    errorData.description = "Non-manifold geometry detected in <span style='color:#ef4444;'>Project_Vault_V2.stl</span>. 124 open edges identified. Automatic repair failed.";
    errorData.primaryTag = "SYSTEM";
    errorData.secondaryTag = "CODE: E-502-CRIT";
    listLayout->addWidget(new NotificationCard(errorData));
}
