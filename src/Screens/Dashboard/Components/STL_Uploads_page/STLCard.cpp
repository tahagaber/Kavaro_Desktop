#include "STLCard.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

STLCard::STLCard(const QString& title, const QString& imagePath, const QString& status, 
                 const QString& size, const QString& triangles, const QString& date, 
                 QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto* card = new QFrame;
    card->setObjectName("stlCard");
    card->setMaximumWidth(380); // Restrict maximum width
    card->setStyleSheet(R"(
        #stlCard {
            background-color: #0f172a; 
            border: 1px solid #1e293b;
            border-radius: 16px;
        }
        #stlCard:hover {
            border-color: #3b82f6;
            background-color: #1e293b;
        }
    )");
    
    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(0, 0, 0, 0);
    cardLayout->setSpacing(0);
    
    // --- Thumbnail Section (Full Width) ---
    auto* imgContainer = new QFrame;
    imgContainer->setFixedHeight(200);
    imgContainer->setStyleSheet("background-color: #020617; border-top-left-radius: 16px; border-top-right-radius: 16px; border: none; overflow: hidden;");
    
    auto* imgLabel = new QLabel(imgContainer);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        imgLabel->setPixmap(pixmap.scaled(380, 200, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        // Removed setScaledContents(true) to prevent stretching/distortion
    } else {
        imgLabel->setText("No Image Available");
        imgLabel->setStyleSheet("color: #334155; font-size: 14px; font-weight: bold;");
    }

    auto* imgMainLayout = new QVBoxLayout(imgContainer);
    imgMainLayout->setContentsMargins(0, 0, 0, 0);
    imgMainLayout->addWidget(imgLabel);

    // Status Badge (Top Right)
    auto* badge = new QLabel(status, imgContainer);
    badge->setObjectName("statusBadge");
    QString badgeColor = (status == "PROCESSED") ? "#10b981" : (status == "OPTIMIZING" ? "#f59e0b" : "#ef4444");
    QString badgeBg = (status == "PROCESSED") ? "rgba(16, 185, 129, 0.2)" : (status == "OPTIMIZING" ? "rgba(245, 158, 11, 0.2)" : "rgba(239, 68, 68, 0.2)");
    
    badge->setStyleSheet(QString(R"(
        #statusBadge {
            background-color: %2;
            color: %1;
            font-size: 10px;
            font-weight: 900;
            padding: 6px 12px;
            border-radius: 6px;
            border: 1px solid %1;
        }
    )").arg(badgeColor, badgeBg));
    
    // Position badge manually to top right
    badge->adjustSize();
    badge->move(350 - badge->width() - 15, 15); // Assume roughly 350 width for card
    badge->raise();

    cardLayout->addWidget(imgContainer);
    
    // --- Info Section ---
    auto* infoWrapper = new QWidget;
    auto* infoLayout = new QVBoxLayout(infoWrapper);
    infoLayout->setContentsMargins(20, 20, 20, 20);
    infoLayout->setSpacing(15);
    
    auto* nameLabel = new QLabel(title);
    nameLabel->setWordWrap(true);
    nameLabel->setStyleSheet("color: #f8fafc; font-size: 17px; font-weight: bold;");
    
    // Metadata Row
    auto* metaRow = new QHBoxLayout;
    metaRow->setSpacing(20);
    
    auto createMetaItem = [](const QString& label, const QString& value) {
        auto* vCol = new QVBoxLayout;
        vCol->setSpacing(4);
        auto* l = new QLabel(label);
        l->setStyleSheet("color: #64748b; font-size: 10px; font-weight: 800; letter-spacing: 0.5px;");
        auto* v = new QLabel(value);
        v->setStyleSheet("color: #cbd5e1; font-size: 12px; font-weight: 600;");
        vCol->addWidget(l);
        vCol->addWidget(v);
        return vCol;
    };
    
    metaRow->addLayout(createMetaItem("SIZE", size));
    metaRow->addLayout(createMetaItem("TRIANGLES", triangles));
    metaRow->addLayout(createMetaItem("DATE", date));
    metaRow->addStretch();
    
    infoLayout->addWidget(nameLabel);
    infoLayout->addLayout(metaRow);
    
    cardLayout->addWidget(infoWrapper);
    
    // --- Actions Row ---
    auto* actionWrapper = new QWidget;
    auto* actionLayout = new QHBoxLayout(actionWrapper);
    actionLayout->setContentsMargins(20, 0, 20, 20);
    actionLayout->setSpacing(10);
    
    auto* viewBtn = new QPushButton("VIEW 3D");
    viewBtn->setFixedHeight(40);
    viewBtn->setCursor(Qt::PointingHandCursor);
    viewBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 8px;
            font-size: 13px;
            font-weight: 800;
        }
        QPushButton:hover { background-color: #2563eb; }
    )");
    
    auto createIconBtn = [](const QString& icon) {
        auto* btn = new QPushButton(icon);
        btn->setFixedSize(40, 40);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #1e293b;
                color: #3b82f6;
                border: 1px solid #334155;
                border-radius: 8px;
                font-size: 16px;
            }
            QPushButton:hover { background-color: #334155; border-color: #3b82f6; }
        )");
        return btn;
    };
    
    actionLayout->addWidget(viewBtn, 1);
    actionLayout->addWidget(createIconBtn("⬇"));
    actionLayout->addWidget(createIconBtn("📤"));
    
    cardLayout->addWidget(actionWrapper);
    layout->addWidget(card);
}
