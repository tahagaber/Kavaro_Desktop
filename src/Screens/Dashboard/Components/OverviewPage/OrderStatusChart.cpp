#include "OrderStatusChart.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

OrderStatusChart::OrderStatusChart(QWidget* parent) : QFrame(parent) {
    setMinimumHeight(240);
    setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
    )");
    
    // Shadow effect
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 4);
    setGraphicsEffect(shadow);
}

void OrderStatusChart::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
    int w = width();
    int h = height();
    
    // Title
    p.setPen(Qt::white);
    p.setFont(QFont("Segoe UI", 14, QFont::Bold));
    p.drawText(25, 35, "Order Processing Status");
    
    struct BarData {
        QString label;
        int value;
        QString startColor;
        QString endColor;
        BarData() = default;
        BarData(QString l, int v, QString sc, QString ec) : label(l), value(v), startColor(sc), endColor(ec) {}
    };
    
    // Data with English labels and gradient colors
    QVector<BarData> data;
    data.push_back(BarData("Completed", m_completed, "#4ade80", "#16a34a")); // Light Green -> Dark Green
    data.push_back(BarData("Pending", m_pending, "#fbbf24", "#d97706"));   // Yellow -> Orange
    data.push_back(BarData("Returned", m_returned, "#f87171", "#dc2626"));  // Light Red -> Dark Red
    
    int maxVal = 0;
    for(const auto& d : data) if(d.value > maxVal) maxVal = d.value;
    if (maxVal < 5) maxVal = 5; // Minimum scale for 3 rows
    else maxVal = maxVal + (maxVal / 4); // Add 25% padding at top

    int barWidth = 45;
    int spacing = (w - (barWidth * 3)) / 4;
    
    int chartBottom = h - 45; // Give more room for bottom labels
    int chartTop = 75;        // Push down so title and top numbers don't clash
    int chartH = chartBottom - chartTop;
    
    // Draw grid lines
    p.setPen(QPen(QColor(51, 65, 85), 1, Qt::DashLine));
    for(int i = 0; i < 4; i++) {
        int y = chartBottom - (i * chartH / 3);
        p.drawLine(20, y, w - 20, y);
    }
    
    for(int i = 0; i < 3; i++) {
        int x = spacing + (i * (barWidth + spacing));
        int barHeight = (data[i].value * chartH) / maxVal;
        // Prevent bar from being completely zero height if value is very low
        if (barHeight < 5) barHeight = 5; 
        int y = chartBottom - barHeight;
        
        // Draw Bar (Gradient)
        QLinearGradient grad(0, y, 0, chartBottom);
        grad.setColorAt(0, QColor(data[i].startColor));
        grad.setColorAt(1, QColor(data[i].endColor));
        
        QPainterPath barPath;
        barPath.addRoundedRect(x, y, barWidth, barHeight, 6, 6);
        p.fillPath(barPath, grad);
        
        // Draw Value above the bar
        p.setFont(QFont("Segoe UI", 10, QFont::Bold));
        p.setPen(QColor(data[i].startColor)); // Use the bright color for the number
        p.drawText(x - 15, y - 25, barWidth + 30, 20, Qt::AlignCenter, QString::number(data[i].value));
        
        // Draw Label below the bar
        p.setFont(QFont("Segoe UI", 10, QFont::Medium));
        p.setPen(QColor(203, 213, 225)); // Lighter gray for better contrast
        p.drawText(x - 20, chartBottom + 12, barWidth + 40, 20, Qt::AlignCenter, data[i].label);
    }
}

void OrderStatusChart::updateData(int completed, int pending, int returned) {
    m_completed = completed;
    m_pending = pending;
    m_returned = returned;
    update(); // trigger repaint
}
