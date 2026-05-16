#include "STLUploadsPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "../Components/STL_Uploads_page/STLHeader.h"
#include "../Components/STL_Uploads_page/STLCategoryTabs.h"
#include "../Components/STL_Uploads_page/STLUploadArea.h"
#include "../Components/STL_Uploads_page/STLGrid.h"
#include "../Components/STL_Uploads_page/STLCard.h"
#include "../Components/STL_Uploads_page/STLPagination.h"

STLUploadsPage::STLUploadsPage(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background-color: transparent; border: none;");

    auto* contentArea = new QWidget;
    contentArea->setStyleSheet("background-color: transparent;");
    auto* contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setContentsMargins(40, 40, 40, 40);
    contentLayout->setSpacing(0);

    contentLayout->addWidget(new STLHeader);
    contentLayout->addWidget(new STLCategoryTabs);

    auto* uploadArea = new STLUploadArea;
    contentLayout->addWidget(uploadArea);

    stlGrid = new STLGrid;
    
    // Initial Mock Cards
    stlGrid->addCard(new STLCard(
        "Futuristic_Warrior_Helmet.stl", 
        "D:/Kavaro_decktop/assets/on_b_5.jpg", 
        "PROCESSED", 
        "24.8 MB", "1.2M", "OCT 12, 2023"
    ));
    
    stlGrid->addCard(new STLCard(
        "Stylized_Anime_Character.stl", 
        "D:/Kavaro_decktop/assets/on_b_2.jpg", 
        "OPTIMIZING", 
        "156.4 MB", "8.4M", "OCT 14, 2023"
    ));
    
    stlGrid->addCard(new STLCard(
        "Mini_Desk_Statue.stl", 
        "D:/Kavaro_decktop/assets/on_b_4.jpg", 
        "PROCESSED", 
        "5.2 MB", "85K", "OCT 15, 2023"
    ));

    contentLayout->addWidget(stlGrid);
    contentLayout->addWidget(new STLPagination(1, 12));
    contentLayout->addStretch();
    
    scrollArea->setWidget(contentArea);
    mainLayout->addWidget(scrollArea);

    // Connect Signal with new signature
    connect(uploadArea, &STLUploadArea::stlAdded, this, &STLUploadsPage::addNewCard);
}

void STLUploadsPage::addNewCard(const QString& name, const QString& details, const QString& category, const QString& imagePath) {
    // Use picked image if available, else use default category thumb
    QString thumb = imagePath;
    if (thumb.isEmpty()) {
        thumb = "D:/Kavaro_decktop/assets/stl_thumbnails/gaming_stl_model.png";
        if (category == "Anime") {
            thumb = "D:/Kavaro_decktop/assets/stl_thumbnails/anime_stl_model.png";
        }
    }
    
    QString size = "Unknown";
    QString triangles = "--";
    QStringList parts = details.split(",");
    if (!parts.isEmpty()) size = parts[0].trimmed();
    if (parts.size() > 1) triangles = parts[1].trimmed();

    auto* newCard = new STLCard(
        name, 
        thumb, 
        "PROCESSED", 
        size, triangles, "TODAY"
    );
    
    stlGrid->addCard(newCard);
}
