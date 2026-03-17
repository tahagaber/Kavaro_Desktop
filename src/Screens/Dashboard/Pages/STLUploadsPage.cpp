#include "STLUploadsPage.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

STLUploadsPage::STLUploadsPage(QWidget* parent) : QWidget(parent) {
    auto* stlLayout = new QVBoxLayout(this);
    stlLayout->setContentsMargins(40, 40, 40, 40);

    auto* stlTitle = new QLabel("Incoming STL Queue");
    stlTitle->setStyleSheet("color: white; font-size: 28px; font-weight: bold; margin-bottom: 20px;");
    stlLayout->addWidget(stlTitle);

    auto* stlGrid = new QGridLayout;
    stlGrid->setSpacing(20);

    // Mock STL File Cards
    for(int i = 0; i < 4; i++) {
        auto* card = new QFrame;
        card->setStyleSheet("background-color: #1e293b; border-radius: 15px; border: 1px solid #334155;");
        card->setFixedSize(220, 180);
        auto* cl = new QVBoxLayout(card);
        
        auto* icon = new QLabel("🧊");
        icon->setAlignment(Qt::AlignCenter);
        icon->setStyleSheet("font-size: 40px; background: #0f172a; border-radius: 10px; margin: 5px;");
        
        auto* name = new QLabel(QString("custom_part_%1.stl").arg(i+1));
        name->setStyleSheet("color: #f8fafc; font-weight: bold;");
        name->setAlignment(Qt::AlignCenter);

        auto* size = new QLabel("12.4 MB | Triangles: 145K");
        size->setStyleSheet("color: #64748b; font-size: 10px;");
        size->setAlignment(Qt::AlignCenter);
        
        auto* btn = new QPushButton("PREVIEW MODEL");
        btn->setStyleSheet("background: #3b82f6; color: white; border-radius: 6px; padding: 8px; font-size: 11px; font-weight: bold;");

        cl->addWidget(icon);
        cl->addWidget(name);
        cl->addWidget(size);
        cl->addWidget(btn);
        
        stlGrid->addWidget(card, i / 2, i % 2);
    }
    stlLayout->addLayout(stlGrid);
    stlLayout->addStretch();
}
