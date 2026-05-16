#include "STLUploadArea.h"
#include "STLAddDialog.h"

STLUploadArea::STLUploadArea(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 40);

    auto* container = new QFrame;
    container->setMinimumHeight(280);
    container->setStyleSheet(R"(
        QFrame {
            background-color: #0f172a;
            border: 2px dashed #1e293b;
            border-radius: 20px;
        }
        QFrame:hover {
            border-color: #3b82f6;
            background-color: rgba(59, 130, 246, 0.05);
        }
    )");
    
    auto* contentLayout = new QVBoxLayout(container);
    contentLayout->setAlignment(Qt::AlignCenter);
    contentLayout->setSpacing(20);
    
    auto* iconFrame = new QFrame;
    iconFrame->setFixedSize(80, 80);
    iconFrame->setStyleSheet("background: #1e293b; border-radius: 40px; border: 1px solid #334155;");
    auto* iconLayout = new QVBoxLayout(iconFrame);
    auto* cloudIcon = new QLabel("📤"); 
    cloudIcon->setAlignment(Qt::AlignCenter);
    cloudIcon->setStyleSheet("font-size: 32px; background: transparent; border: none; color: #3b82f6;");
    iconLayout->addWidget(cloudIcon);
    
    auto* dropTitle = new QLabel("DROP YOUR STL FILES HERE");
    dropTitle->setAlignment(Qt::AlignCenter);
    dropTitle->setStyleSheet("color: #f8fafc; font-size: 20px; font-weight: 800; background: transparent; border: none;");
    
    auto* dropDesc = new QLabel("Securely upload spatial data models for optimization\nand 3D rendering. Supported formats: .STL, .OBJ, .STEP");
    dropDesc->setAlignment(Qt::AlignCenter);
    dropDesc->setStyleSheet("color: #64748b; font-size: 14px; line-height: 1.6; background: transparent; border: none;");
    
    auto* selectBtn = new QPushButton("Select Files from Local Disk");
    selectBtn->setFixedSize(260, 48);
    selectBtn->setCursor(Qt::PointingHandCursor);
    selectBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 12px;
            font-size: 15px;
            font-weight: bold;
            border: none;
        }
        QPushButton:hover { background-color: #2563eb; }
    )");
    
    connect(selectBtn, &QPushButton::clicked, this, &STLUploadArea::handleUploadClick);
    
    contentLayout->addStretch();
    contentLayout->addWidget(iconFrame, 0, Qt::AlignCenter);
    contentLayout->addWidget(dropTitle);
    contentLayout->addWidget(dropDesc);
    contentLayout->addSpacing(10);
    contentLayout->addWidget(selectBtn, 0, Qt::AlignCenter);
    contentLayout->addStretch();
    
    layout->addWidget(container);
}

void STLUploadArea::handleUploadClick() {
    STLAddDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        emit stlAdded(dialog.getModelName(), dialog.getModelDetails(), dialog.getCategory(), dialog.getImagePath());
    }
}
