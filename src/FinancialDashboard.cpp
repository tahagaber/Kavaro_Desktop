#include "FinancialDashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QPainter>
#include <QTimer>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>

// ==================== Custom Chart Widget ====================
// ==================== Custom Chart Widget ====================

LineChart::LineChart(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(300);
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

void LineChart::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
    int w = width();
    int h = height();
    int margins = 40;
    int chartH = h - margins;
    
    // Draw grid lines
    QPen gridPen(QColor("#334155"), 1, Qt::DashLine);
    p.setPen(gridPen);
    for(int i = 0; i < 4; i++) {
        int y = chartH - (i * chartH / 3);
        if(i > 0) p.drawLine(margins, y, w - margins, y);
    }
    
    // Draw labels
    p.setPen(QColor("#64748b"));
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
    QPen targetPen(QColor("#64748b"), 2, Qt::DashLine);
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
    p.setPen(QPen(QColor("#3b82f6"), 3));
    QPainterPath linePath;
    createSmoothPath(revenueData, linePath, false);
    p.drawPath(linePath);
}


// ==================== Custom Vertical Bar Chart Widget ====================
// ==================== Custom Vertical Bar Chart Widget ====================

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
    p.setPen(QColor("#ffffff"));
    p.setFont(QFont("Segoe UI", 14, QFont::Bold));
    p.drawText(25, 35, "Order Processing Status");
    
    struct BarData {
        QString label;
        int value;
        QString startColor;
        QString endColor;
    };
    
    // Data with English labels and gradient colors
    QVector<BarData> data = {
        {"Completed", 2450, "#4ade80", "#16a34a"},  // Light Green -> Dark Green
        {"Pending", 850, "#fbbf24", "#d97706"},     // Yellow -> Orange
        {"Returned", 120, "#f87171", "#dc2626"}     // Light Red -> Dark Red
    };
    
    int maxVal = 3000; // Increased to give the values breathing room at the top
    int barWidth = 45;
    int spacing = (w - (barWidth * 3)) / 4;
    
    int chartBottom = h - 45; // Give more room for bottom labels
    int chartTop = 75;        // Push down so title and top numbers don't clash
    int chartH = chartBottom - chartTop;
    
    // Draw grid lines
    p.setPen(QPen(QColor("#334155"), 1, Qt::DashLine));
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
        p.setPen(QColor("#cbd5e1")); // Lighter gray for better contrast
        p.drawText(x - 20, chartBottom + 12, barWidth + 40, 20, Qt::AlignCenter, data[i].label);
    }
}


// ==================== Metric Card ====================
// ==================== Metric Card ====================

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
    )").arg(bgColor).arg(accentColor));
    
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



// ==================== AI Insight Item ====================

InsightItem::InsightItem(const QString& type, const QString& content, 
                         QWidget* parent) : QFrame(parent) {
    
    setFrameStyle(QFrame::NoFrame);
    setStyleSheet(R"(
        InsightItem {
            background-color: #1e293b;
            border-radius: 8px;
        }
    )");
    
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(15, 12, 15, 12);
    layout->setSpacing(6);
    
    // Type label
    auto* typeLabel = new QLabel(type);
    QString typeColor = (type == "System Recommendation") ? "#94a3b8" :
                       (type == "Anomaly Detected") ? "#f97316" : "#22c55e";
    typeLabel->setStyleSheet(QString("color: %1; font-size: 11px;").arg(typeColor));
    layout->addWidget(typeLabel);
    
    // Content with highlighted text
    auto* contentLabel = new QLabel(content);
    contentLabel->setWordWrap(true);
    contentLabel->setStyleSheet(R"(
        color: #e2e8f0;
        font-size: 13px;
        line-height: 1.4;
    )");
    layout->addWidget(contentLabel);
}


// ==================== Main Window ====================

FinancialDashboard::FinancialDashboard(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Kavaro");
    resize(1300, 600);
    
    // Central widget
    auto* central = new QWidget;
    central->setStyleSheet("background-color: #0f172a;");
    setCentralWidget(central);
    
    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // ========== TOP NAVBAR ==========
    auto* navbar = new QFrame;
    navbar->setFixedHeight(70);
    navbar->setStyleSheet(R"(
        QFrame {
            background-color: #0b1120;
            border-bottom: 1px solid #1e293b;
        }
    )");
    
    auto* navLayout = new QHBoxLayout(navbar);
    navLayout->setContentsMargins(30, 0, 30, 0);
    navLayout->setSpacing(10);
    
    // Logo
    auto* logo = new QLabel("◆ KAVARO");
    logo->setStyleSheet(R"(
        color: #ffffff; 
        font-size: 20px; 
        font-weight: 900;
        letter-spacing: 2px;
    )");
    navLayout->addWidget(logo);
    navLayout->addSpacing(40);
    
    // Nav buttons
    QStringList navItems = {"Command Center", "Model Lab", "Analytics", "Finance Studio"};
    for(const auto& item : navItems) {
        auto* btn = new QPushButton(item);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setCheckable(true);
        btn->setChecked(item == "Command Center");
        btn->setStyleSheet(R"(
            QPushButton {
                background: transparent;
                color: #94a3b8;
                border: none;
                padding: 10px 18px;
                font-size: 14px;
                font-weight: 600;
                border-radius: 8px;
            }
            QPushButton:hover {
                color: #f8fafc;
                background-color: rgba(255, 255, 255, 0.05);
            }
            QPushButton:checked {
                background-color: rgba(59, 130, 246, 0.15);
                color: #3b82f6;
                border: 1px solid rgba(59, 130, 246, 0.3);
            }
        )");
        navLayout->addWidget(btn);
    }
    
    navLayout->addStretch();
    
    // Search
    auto* search = new QLineEdit;
    search->setPlaceholderText("🔍 Search Kavaro systems...");
    search->setFixedWidth(280);
    search->setStyleSheet(R"(
        QLineEdit {
            background-color: #1e293b;
            border: 1px solid #334155;
            border-radius: 8px;
            padding: 8px 15px;
            color: #f8fafc;
            font-size: 13px;
        }
        QLineEdit:focus {
            border: 1px solid #3b82f6;
        }
    )");
    navLayout->addWidget(search);
    navLayout->addSpacing(20);
    
    // User profile
    auto* userBtn = new QPushButton("Admin");
    userBtn->setCursor(Qt::PointingHandCursor);
    userBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #e2e8f0;
            color: #0f172a;
            font-weight: bold;
            border-radius: 16px;
            padding: 6px 20px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #ffffff;
        }
    )");
    navLayout->addWidget(userBtn);
    
    mainLayout->addWidget(navbar);
    
    // Main Body (Sidebar + Content)
    auto* bodyWidget = new QWidget;
    auto* bodyLayout = new QHBoxLayout(bodyWidget);
    bodyLayout->setContentsMargins(0, 0, 0, 0);
    bodyLayout->setSpacing(0);
    mainLayout->addWidget(bodyWidget, 1);
    
    // ========== SIDEBAR (Vertical Tabs) ==========
    auto* sidebar = new QFrame;
    sidebar->setFixedWidth(220);
    sidebar->setStyleSheet("background-color: #0f172a; border-right: 1px solid #1e293b;");
    
    auto* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(0, 20, 0, 0);
    sidebarLayout->setSpacing(5);
    
    QStringList tabNames = {"Overview", "Revenue Analytics", "Burn Rate", 
                           "ROI Projections", "Market Data"};
    for(int i = 0; i < tabNames.size(); i++) {
        auto* tab = new QPushButton("   " + tabNames[i]);
        tab->setCheckable(true);
        tab->setChecked(i == 0);
        tab->setStyleSheet(R"(
            QPushButton {
                text-align: left;
                background: transparent;
                color: #94a3b8;
                border: none;
                border-left: 3px solid transparent;
                padding: 15px 20px;
                font-size: 14px;
            }
            QPushButton:hover {
                background-color: #1e293b;
                color: #f8fafc;
            }
            QPushButton:checked {
                color: #3b82f6;
                background-color: #1e293b;
                border-left: 3px solid #3b82f6;
                font-weight: bold;
            }
        )");
        sidebarLayout->addWidget(tab);
    }
    sidebarLayout->addStretch();
    bodyLayout->addWidget(sidebar);
    
    // ========== CONTENT AREA ==========
    auto* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(R"(
        QScrollArea {
            background-color: transparent;
            border: none;
        }
        QScrollBar:vertical {
            border: none;
            background: #0f172a;
            width: 8px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #334155;
            min-height: 20px;
            border-radius: 4px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )");

    auto* contentArea = new QWidget;
    contentArea->setStyleSheet("background-color: transparent;");
    auto* contentLayout = new QHBoxLayout(contentArea);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(20);
    
    // LEFT COLUMN (Charts + Table)
    auto* leftCol = new QWidget;
    auto* leftLayout = new QVBoxLayout(leftCol);
    leftLayout->setSpacing(20);
    
    // --- Metric Cards ---
    auto* cardsRow = new QHBoxLayout;
    cardsRow->setSpacing(15);
    
    cardsRow->addWidget(new MetricCard("TOTAL REVENUE", "$20K",
                                      "↑ +12.5% vs last month", "blue"));
    cardsRow->addWidget(new MetricCard("MONTHLY BURN", "$1.4K",
                                      "↓ -4.2% Optimized", "orange"));
    cardsRow->addWidget(new MetricCard("PORTFOLIO ROI", "+2.8%",
                                      "↑ +3.1% Target exceeded", "green"));
    cardsRow->addWidget(new MetricCard("COMPUTE COST", "$50K",
                                      "→ Stable H100 Clusters", "gray"));
    
    leftLayout->addLayout(cardsRow);
    
    // --- Chart Section ---
    auto* chartCard = new QFrame;
    chartCard->setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
    )");
    
    auto* chartLayout = new QVBoxLayout(chartCard);
    chartLayout->setContentsMargins(20, 20, 20, 20);
    
    // Chart header
    auto* chartHeader = new QHBoxLayout;
    auto* chartTitle = new QLabel("Multi-Currency Growth (USD/EUR/JPY)");
    chartTitle->setStyleSheet("color: #f8fafc; font-size: 16px; font-weight: bold;");
    
    auto* chartSubtitle = new QLabel("Projected scaling vs actual performance");
    chartSubtitle->setStyleSheet("color: #64748b; font-size: 12px;");
    
    auto* titleCol = new QVBoxLayout;
    titleCol->addWidget(chartTitle);
    titleCol->addWidget(chartSubtitle);
    
    chartHeader->addLayout(titleCol);
    chartHeader->addStretch();
    
    // Legend
    auto* legend = new QHBoxLayout;
    
    auto* revPill = new QFrame;
    revPill->setStyleSheet("background-color: #0f172a; border-radius: 6px;");
    auto* revPillLayout = new QHBoxLayout(revPill);
    revPillLayout->setContentsMargins(10, 5, 10, 5);
    auto* revDot = new QLabel("●");
    revDot->setStyleSheet("color: #3b82f6; font-size: 10px;");
    auto* revTxt = new QLabel("Revenue");
    revTxt->setStyleSheet("color: #e2e8f0; font-size: 11px;");
    revPillLayout->addWidget(revDot);
    revPillLayout->addWidget(revTxt);
    
    auto* tgtPill = new QFrame;
    tgtPill->setStyleSheet("background-color: #0f172a; border-radius: 6px;");
    auto* tgtPillLayout = new QHBoxLayout(tgtPill);
    tgtPillLayout->setContentsMargins(10, 5, 10, 5);
    auto* tgtDot = new QLabel("●");
    tgtDot->setStyleSheet("color: #64748b; font-size: 10px;");
    auto* tgtTxt = new QLabel("Target");
    tgtTxt->setStyleSheet("color: #94a3b8; font-size: 11px;");
    tgtPillLayout->addWidget(tgtDot);
    tgtPillLayout->addWidget(tgtTxt);
    
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
    
    legend->addWidget(revPill);
    legend->addWidget(tgtPill);
    legend->addSpacing(20);
    legend->addWidget(periodCombo);
    chartHeader->addLayout(legend);
    
    chartLayout->addLayout(chartHeader);
    
    // Chart widget
    auto* lineChart = new LineChart;
    chartLayout->addWidget(lineChart);
    
    // Connect combo box to update chart
    connect(periodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), [lineChart, chartTitle](int index) {
        if (index == 0) {
            lineChart->setViewMode(LineChart::Months12);
            chartTitle->setText("Multi-Currency Growth (12 Months)");
        } else if (index == 1) {
            lineChart->setViewMode(LineChart::Days30);
            chartTitle->setText("Multi-Currency Growth (30 Days)");
        } else if (index == 2) {
            lineChart->setViewMode(LineChart::Days7);
            chartTitle->setText("Multi-Currency Growth (7 Days)");
        }
    });
    
    leftLayout->addWidget(chartCard, 2);
    
    // --- Transaction Table ---
    auto* tableCard = new QFrame;
    tableCard->setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
        QTableWidget {
            background-color: transparent;
            border: none;
            color: #e2e8f0;
            gridline-color: #334155;
        }
        QHeaderView::section {
            background-color: transparent;
            color: #64748b;
            padding: 10px;
            border: none;
            font-size: 11px;
            font-weight: 600;
        }
        QTableWidget::item {
            padding: 12px;
            border-bottom: 1px solid #334155;
        }
    )");
    
    auto* tableLayout = new QVBoxLayout(tableCard);
    tableLayout->setContentsMargins(20, 20, 20, 20);
    
    auto* tableHeader = new QHBoxLayout;
    auto* tableTitle = new QLabel("Recent 3D Print Orders");
    tableTitle->setStyleSheet("color: #f8fafc; font-size: 16px; font-weight: bold;");
    tableHeader->addWidget(tableTitle);
    tableHeader->addStretch();
    
    auto* exportBtn = new QPushButton("Export CSV");
    exportBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #334155;
            color: #94a3b8;
            border-radius: 6px;
            padding: 6px 12px;
            font-size: 12px;
        }
    )");
    tableHeader->addWidget(exportBtn);
    
    auto* filterBtn = new QPushButton("Filter");
    filterBtn->setStyleSheet(exportBtn->styleSheet());
    tableHeader->addWidget(filterBtn);
    
    tableLayout->addLayout(tableHeader);
    
    // Table
    auto* table = new QTableWidget(3, 7);
    table->setHorizontalHeaderLabels(
        QStringList() << "ORDER ID" << "CLIENT NAME" << "3D MODEL / ITEM" 
                     << "PRINT TYPE" << "STATUS" << "DATE" << "VIEW");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Give remaining space to the 3D model column
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Sample data
    QStringList ids = {"#PRN-1042", "#PRN-1043", "#PRN-1044"};
    QStringList clients = {"Ahmed Hassan", "Sarah Connor", "Kavaro Studio"};
    QStringList models = {"Spider-Man Bust (20cm)", "Darth Vader Helmet", "Custom Gear Assembly"};
    QStringList types = {"Resin (Grey)", "PLA (Black)", "PETG (White)"};
    QStringList statuses = {"COMPLETED", "PENDING", "RETURNED"};
    QStringList statusColors = {"#22c55e", "#f59e0b", "#ef4444"};
    QStringList timestamps = {"04 Mar 2026, 14:21", "04 Mar 2026, 13:05", "03 Mar 2026, 11:45"};
    
    for(int row = 0; row < 3; row++) {
        table->setItem(row, 0, new QTableWidgetItem(ids[row]));
        table->setItem(row, 1, new QTableWidgetItem(clients[row]));
        
        auto* modelItem = new QTableWidgetItem(models[row]);
        modelItem->setFont(QFont("Segoe UI", 10, QFont::Bold));
        table->setItem(row, 2, modelItem);
        
        table->setItem(row, 3, new QTableWidgetItem(types[row]));
        
        auto* statusItem = new QTableWidgetItem("  " + statuses[row] + "  ");
        statusItem->setBackground(QColor(statusColors[row]).darker(150));
        statusItem->setForeground(QColor(statusColors[row]));
        statusItem->setFont(QFont("Segoe UI", 9, QFont::Bold));
        statusItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 4, statusItem);
        
        table->setItem(row, 5, new QTableWidgetItem(timestamps[row]));
        
        auto* viewItem = new QTableWidgetItem("");
        viewItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 6, viewItem);
    }
    
    tableLayout->addWidget(table);
    leftLayout->addWidget(tableCard, 1);
    
    contentLayout->addWidget(leftCol, 3);
    
    // RIGHT COLUMN (AI Insights)
    auto* rightCol = new QWidget;
    rightCol->setFixedWidth(350);
    auto* rightLayout = new QVBoxLayout(rightCol);
    rightLayout->setSpacing(15);
    
    // AI Insights Card
    auto* insightsCard = new QFrame;
    insightsCard->setStyleSheet(R"(
        QFrame {
            background-color: #1e293b;
            border-radius: 12px;
        }
    )");
    
    auto* insightsLayout = new QVBoxLayout(insightsCard);
    insightsLayout->setContentsMargins(20, 20, 20, 20);
    insightsLayout->setSpacing(15);
    
    // Header
    auto* insightsHeader = new QHBoxLayout;
    auto* insightsTitle = new QLabel("✨ AI Insights");
    insightsTitle->setStyleSheet("color: #f8fafc; font-size: 16px; font-weight: bold;");
    auto* liveBadge = new QLabel("LIVE");
    liveBadge->setStyleSheet(R"(
        background-color: #3b82f6;
        color: white;
        padding: 2px 8px;
        border-radius: 4px;
        font-size: 10px;
    )");
    
    insightsHeader->addWidget(insightsTitle);
    insightsHeader->addStretch();
    insightsHeader->addWidget(liveBadge);
    insightsLayout->addLayout(insightsHeader);
    
    // Insights items
    insightsLayout->addWidget(new InsightItem("System Recommendation",
        "Revenue in JPY is currently 12% below projections due to currency fluctuations. "
        "Hedge advised."));
    
    insightsLayout->addWidget(new InsightItem("Anomaly Detected",
        "Unusual spike in compute costs in <span style='color:#f97316;'>Region US-East-1</span>. "
        "Investigate potential GPU leak."));
    
    insightsLayout->addWidget(new InsightItem("Portfolio Alert",
        "Production Studio ROI hit <span style='color:#22c55e;'>32% milestone</span>. "
        "Recommend re-investment in Tier 2 AI Agents."));
    
    // Generate report button
    auto* reportBtn = new QPushButton("GENERATE FULL REPORT");
    reportBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #334155;
            color: #3b82f6;
            border: 1px solid #3b82f6;
            border-radius: 8px;
            padding: 12px;
            font-size: 12px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #3b82f6;
            color: white;
        }
    )");
    insightsLayout->addWidget(reportBtn);
    
    rightLayout->addWidget(insightsCard);
    
    // Order Status Chart (Replaces Production Scaler)
    auto* orderChart = new OrderStatusChart;
    rightLayout->addWidget(orderChart);
    
    contentLayout->addWidget(rightCol);
    
    scrollArea->setWidget(contentArea);
    bodyLayout->addWidget(scrollArea, 1);
}
