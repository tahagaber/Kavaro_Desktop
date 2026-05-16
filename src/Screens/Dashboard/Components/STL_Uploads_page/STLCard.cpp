#include "STLCard.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>

STLCard::STLCard(const QString& title, const QString& imagePath, const QString& status, 
                 const QString& size, const QString& triangles, const QString& date, 
                 QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto* card = new QFrame;
    card->setObjectName("stlCard");
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
    imgContainer->setFixedHeight(220); // Larger height for better visual
    imgContainer->setStyleSheet("background-color: #020617; border-top-left-radius: 16px; border-top-right-radius: 16px; border: none;");
    
    auto* imgLabel = new QLabel(imgContainer);
    imgLabel->setMinimumSize(1, 1); // Allow scaling
    imgLabel->setAlignment(Qt::AlignCenter);
    
    // Auto-scale pixmap to fill width
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        imgLabel->setPixmap(pixmap.scaled(400, 220, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    } else {
        imgLabel->setText("No Image Available");
        imgLabel->setStyleSheet("color: #334155; font-size: 14px; font-weight: bold;");
    }
    
    // Status Badge (Top Right)
    auto* badge = new QLabel(status, imgContainer);
    badge->setObjectName("statusBadge");
    QString badgeColor = (status == "PROCESSED") ? "#10b981" : (status == "OPTIMIZING" ? "#f59e0b" : "#ef4444");
    QString badgeBg = (status == "PROCESSED") ? "rgba(16, 185, 129, 0.15)" : (status == "OPTIMIZING" ? "rgba(245, 158, 11, 0.15)" : "rgba(239, 68, 68, 0.15)");
    
    badge->setStyleSheet(QString(R"(
        #statusBadge {
            background-color: %2;
            color: %1;
            font-size: 11px;
            font-weight: 800;
            padding: 6px 12px;
            border-radius: 8px;
            border: 1px solid %1;
        }
    )").arg(badgeColor, badgeBg));
    
    // Position badge in constructor (will be adjusted in layout but for now)
    auto* badgeLayout = new QHBoxLayout(imgContainer);
    badgeLayout->addStretch();
    badgeLayout->addWidget(badge);
    badgeLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    badgeLayout->setContentsMargins(15, 15, 15, 15);

    auto* imgMainLayout = new QVBoxLayout(imgContainer);
    imgMainLayout->setContentsMargins(0, 0, 0, 0);
    imgMainLayout->addWidget(imgLabel);

    cardLayout->addWidget(imgContainer);
    
    // --- Info Section ---
    auto* infoWrapper = new QWidget;
    auto* infoLayout = new QVBoxLayout(infoWrapper);
    infoLayout->setContentsMargins(20, 20, 20, 20);
    infoLayout->setSpacing(15);
    
    auto* nameLabel = new QLabel(title);
    nameLabel->setWordWrap(true);
    nameLabel->setStyleSheet("color: #f8fafc; font-size: 18px; font-weight: bold; font-family: 'Inter', sans-serif;");
    
    // Metadata Row
    auto* metaRow = new QHBoxLayout;
    metaRow->setSpacing(25);
    
    auto createMetaItem = [](const QString& label, const QString& value) {
        auto* vCol = new QVBoxLayout;
        vCol->setSpacing(4);
        auto* l = new QLabel(label);
        l->setStyleSheet("color: #64748b; font-size: 11px; font-weight: bold; letter-spacing: 1px; text-transform: uppercase;");
        auto* v = new QLabel(value);
        v->setStyleSheet("color: #cbd5e1; font-size: 13px; font-weight: 600;");
        vCol->addWidget(l);
        vCol->addWidget(v);
        return vCol;
    };
    
    metaRow->addLayout(createMetaItem("Size", size));
    metaRow->addLayout(createMetaItem("Triangles", triangles));
    metaRow->addLayout(createMetaItem("Date", date));
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
    viewBtn->setFixedHeight(44);
    viewBtn->setCursor(Qt::PointingHandCursor);
    viewBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 10px;
            font-size: 14px;
            font-weight: bold;
            border: none;
        }
        QPushButton:hover {
            background-color: #2563eb;
        }
    )");
    
    auto createIconBtn = [](const QString& icon) {
        auto* btn = new QPushButton(icon);
        btn->setFixedSize(44, 44);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #1e293b;
                color: #94a3b8;
                border: 1px solid #334155;
                border-radius: 10px;
                font-size: 18px;
            }
            QPushButton:hover {
                background-color: #334155;
                color: #f8fafc;
                border-color: #475569;
            }
        )");
        return btn;
    };
    
    auto* downloadBtn = createIconBtn("⬇");
    auto* shareBtn = createIconBtn("📤");
    
    actionLayout->addWidget(viewBtn, 1);
    actionLayout->addWidget(downloadBtn);
    actionLayout->addWidget(shareBtn);
    
    cardLayout->addWidget(actionWrapper);
    
    layout->addWidget(card);
}
