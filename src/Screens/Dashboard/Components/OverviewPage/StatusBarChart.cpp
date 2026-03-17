#include "StatusBarChart.h"
#include <QPainter>
#include <QPainterPath>

StatusBarChart::StatusBarChart(QWidget* parent) : QWidget(parent) {
    setFixedSize(300, 330);
}

void StatusBarChart::setData(int delivered, int pending, int returned) {
    m_delivered = delivered;
    m_pending = pending;
    m_returned = returned;
    update();
}

void StatusBarChart::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Header Title (Simple text)
    painter.setPen(QColor("#94a3b8"));
    painter.setFont(QFont("Segoe UI", 11, QFont::Bold));
    painter.drawText(0, 20, width(), 30, Qt::AlignCenter, "ORDER STATISTICS");

    int margin = 35;
    int topMargin = 80;
    int bottomMargin = 50;
    int w = width() - 2 * margin;
    int h = height() - topMargin - bottomMargin;
    int barWidth = 50;
    int spacing = (w - (3 * barWidth)) / 2;

    int total = m_delivered + m_pending + m_returned;
    if (total == 0) total = 1;

    auto drawBar = [&](int val, int index, QColor mainColor, QString label) {
        int x = margin + index * (barWidth + spacing);
        int barHeight = (val * h) / total;
        int y = height() - bottomMargin - barHeight;

        // Draw background track (light gray for better visual context)
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(51, 65, 85, 80)); // Slate 700 with alpha
        painter.drawRoundedRect(x, topMargin, barWidth, h, 6, 6);

        // Draw actual bar
        painter.setBrush(mainColor);
        painter.drawRoundedRect(x, y, barWidth, barHeight, 6, 6);

        // Value text
        painter.setPen(Qt::white);
        painter.setFont(QFont("Segoe UI", 9, QFont::Bold));
        painter.drawText(x, y - 25, barWidth, 20, Qt::AlignCenter, QString::number(val));

        // Label Footer (Simple text)
        painter.setPen(QColor("#94a3b8"));
        painter.setFont(QFont("Segoe UI", 8));
        painter.drawText(x - 10, height() - 30, barWidth + 20, 20, Qt::AlignCenter, label);
    };

    drawBar(m_delivered, 0, QColor("#22c55e"), "Delivered");
    drawBar(m_pending, 1, QColor("#3b82f6"), "Pending");
    drawBar(m_returned, 2, QColor("#ef4444"), "Returned");
}

