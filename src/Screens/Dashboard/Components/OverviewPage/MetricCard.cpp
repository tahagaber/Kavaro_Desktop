#include "MetricCard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

MetricCard::MetricCard(const QString& title, const QString& value, 
                       const QString& subtitle, const QString& color,
                       QWidget* parent) : QFrame(parent) {
    
    setFixedHeight(120);
    setFrameStyle(QFrame::NoFrame);
    
    // Shadow effect
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 4);
    setGraphicsEffect(shadow);
    
    // Colors
    QString bgColor = "#1e293b";
    QString accentColor;
    if(color == "blue") accentColor = "#3b82f6";
    else if(color == "orange") accentColor = "#f97316";
    else if(color == "green") accentColor = "#22c55e";
    else accentColor = "#64748b";
    
    setStyleSheet(QString(R"(
        MetricCard {
            background-color: %1;
            border-radius: 12px;
            border-left: 4px solid %2;
        }
        QLabel {
            background: transparent;
        }
    )").arg(bgColor, accentColor));
    
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 15, 20, 15);
    layout->setSpacing(8);
    
    // Title
    auto* titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: #94a3b8; font-size: 12px; font-weight: 600;");
    layout->addWidget(titleLabel);
    
    // Value
    auto* valueLabel = new QLabel(value);
    valueLabel->setStyleSheet("color: #f8fafc; font-size: 28px; font-weight: bold;");
    layout->addWidget(valueLabel);
    
    // Subtitle with icon
    auto* subLayout = new QHBoxLayout;
    subLayout->setSpacing(5);
    
    QString arrow = subtitle.contains("+") ? "↑" : (subtitle.contains("-") ? "↓" : "→");
    QString subColor = subtitle.contains("+") ? "#22c55e" : 
                      (subtitle.contains("-") ? "#f97316" : "#64748b");
    
    auto* arrowLabel = new QLabel(arrow);
    arrowLabel->setStyleSheet(QString("color: %1; font-size: 12px;").arg(subColor));
    
    auto* subLabel = new QLabel(subtitle);
    subLabel->setStyleSheet(QString("color: %1; font-size: 12px;").arg(subColor));
    
    subLayout->addWidget(arrowLabel);
    subLayout->addWidget(subLabel);
    subLayout->addStretch();
    
    layout->addLayout(subLayout);
}
