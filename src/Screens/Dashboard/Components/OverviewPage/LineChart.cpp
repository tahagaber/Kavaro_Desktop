#include "LineChart.h"
#include <QPainter>
#include <QPainterPath>

LineChart::LineChart(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(230);
    setViewMode(Months12);
}

void LineChart::setViewMode(ViewMode mode) {
    revenueData.clear();
    targetData.clear();
    labels.clear();
    
    if (mode == Months12) {
        revenueData = {20, 22, 21, 35, 45, 52, 68, 65, 70, 75, 85, 92};
        targetData = {18, 20, 22, 28, 35, 42, 48, 55, 62, 68, 75, 82};
        labels = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
                  "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    } else if (mode == Days30) {
        revenueData = {35, 38, 34, 42, 45, 50, 48, 55, 60, 62, 68, 70, 75, 80, 85};
        targetData =  {30, 32, 35, 38, 40, 45, 48, 50, 52, 55, 60, 65, 70, 75, 80};
        labels = {"1", "3", "5", "7", "9", "11", "13", "15", "17", "19", "21", "23", "25", "27", "30"};
    } else if (mode == Days7) {
        revenueData = {65, 59, 72, 80, 85, 76, 90};
        targetData = {60, 62, 68, 75, 82, 80, 88};
        labels = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    }
    update();
}

QComboBox* LineChart::createPeriodSelector(QLabel* titleLabel) {
    auto* periodCombo = new QComboBox;
    periodCombo->setCursor(Qt::PointingHandCursor);
    periodCombo->addItems({"Last 12 Months", "Last 30 Days", "Last 7 Days"});
    periodCombo->setStyleSheet(R"(
        QComboBox {
            background-color: #334155;
            color: #94a3b8;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 12px;
            border: none;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: #1e293b;
            color: #f8fafc;
            selection-background-color: #3b82f6;
            border: 1px solid #334155;
            border-radius: 4px;
        }
    )");

    connect(periodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), [this, titleLabel](int index) {
        if (index == 0) {
            this->setViewMode(LineChart::Months12);
            if (titleLabel) titleLabel->setText("Multi-Currency Growth (12 Months)");
        } else if (index == 1) {
            this->setViewMode(LineChart::Days30);
            if (titleLabel) titleLabel->setText("Multi-Currency Growth (30 Days)");
        } else if (index == 2) {
            this->setViewMode(LineChart::Days7);
            if (titleLabel) titleLabel->setText("Multi-Currency Growth (7 Days)");
        }
    });

    return periodCombo;
}

void LineChart::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
    int w = width();
    int h = height();
    int margins = 40;
    int chartH = h - margins;
    
    // Draw grid lines
    QPen gridPen(QColor(51, 65, 85), 1, Qt::DashLine);
    p.setPen(gridPen);
    for(int i = 0; i < 4; i++) {
        int y = chartH - (i * chartH / 3);
        if(i > 0) p.drawLine(margins, y, w - margins, y);
    }
    
    // Draw labels
    p.setPen(QColor(100, 116, 139));
    p.setFont(QFont("Segoe UI", 8, QFont::Bold));
    int count = labels.size();
    for(int i = 0; i < count; i++) {
        int x = margins + (i * (w - 2 * margins) / (count - 1));
        // Corrected Y positioning so labels are perfectly visible
        p.drawText(x - 20, chartH + 10, 40, 20, Qt::AlignCenter, labels[i]);
    }
    
    // Smooth curve helper lambda
    auto createSmoothPath = [&](const QVector<int>& data, QPainterPath& path, bool closePath) {
        int prevX = 0, prevY = 0;
        for(int i = 0; i < data.size(); i++) {
            int x = margins + (i * (w - 2 * margins) / (data.size() - 1));
            int y = chartH - (data[i] * chartH / 100);
            
            if(i == 0) {
                if (closePath) {
                    path.moveTo(x, chartH);
                    path.lineTo(x, y);
                } else {
                    path.moveTo(x, y);
                }
            } else {
                int cpX = (prevX + x) / 2;
                path.cubicTo(cpX, prevY, cpX, y, x, y);
            }
            prevX = x;
            prevY = y;
        }
        if (closePath && data.size() > 0) {
            path.lineTo(prevX, chartH);
            path.closeSubpath();
        }
    };

    // Draw target line (dashed)
    QPen targetPen(QColor(100, 116, 139), 2, Qt::DashLine);
    p.setPen(targetPen);
    QPainterPath targetPath;
    createSmoothPath(targetData, targetPath, false);
    p.drawPath(targetPath);
    
    // Draw revenue area (gradient fill)
    QLinearGradient grad(0, 0, 0, chartH);
    grad.setColorAt(0, QColor(59, 130, 246, 50)); // #3b82f6 with transparency
    grad.setColorAt(1, QColor(59, 130, 246, 0));
    
    QPainterPath revenueAreaPath;
    createSmoothPath(revenueData, revenueAreaPath, true);
    p.fillPath(revenueAreaPath, QBrush(grad));
    
    // Draw revenue line
    p.setPen(QPen(QColor(59, 130, 246), 3));
    QPainterPath linePath;
    createSmoothPath(revenueData, linePath, false);
    p.drawPath(linePath);
}
