#include "OverviewPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "../Components/OverviewPage/LineChart.h"
#include "../Components/OverviewPage/MiniCalendar.h"
#include "../Components/OverviewPage/StatusBarChart.h"
#include "../Components/OverviewPage/MetricCard.h"
#include "../Components/OverviewPage/RecentOrdersTable.h"

OverviewPage::OverviewPage(QWidget* parent) : QWidget(parent) {
    auto* overviewLayout = new QVBoxLayout(this);
    overviewLayout->setContentsMargins(0, 0, 0, 0);

    // --- MAIN SCROLL AREA ---
    scrollArea = new QScrollArea;
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
    contentLayout->setContentsMargins(15, 15, 15, 15);
    contentLayout->setSpacing(15);
    
    // =========================================================================
    // LEFT COLUMN (Metric Cards, Charts, Tables)
    // =========================================================================
    auto* leftCol = new QWidget;
    auto* leftLayout = new QVBoxLayout(leftCol);
    leftLayout->setSpacing(20);
    
    // --- 1. METRIC CARDS ROW ---
    // File: ../Components/OverviewPage/MetricCard.h/cpp
    auto* cardsRow = new QHBoxLayout;
    cardsRow->setSpacing(10);
    
    cardsRow->addWidget(new MetricCard("TOTAL REVENUE", "$20K", "↑ +12.5% vs last month", "blue"));
    cardsRow->addWidget(new MetricCard("MONTHLY BURN", "$1.4K", "↓ -4.2% Optimized", "orange"));
    cardsRow->addWidget(new MetricCard("PORTFOLIO ROI", "+2.8%", "↑ +3.1% Target exceeded", "green"));
    cardsRow->addWidget(new MetricCard("COMPUTE COST", "$50K", "→ Stable H100 Clusters", "gray"));
    
    leftLayout->addLayout(cardsRow);
    
    // --- 2. MULTI-CURRENCY GROWTH CHART ---
    // File: ../Components/OverviewPage/LineChart.h/cpp
    auto* chartCard = new QFrame;
    chartCard->setStyleSheet("QFrame { background-color: #1e293b; border-radius: 12px; }");
    
    auto* chartLayout = new QVBoxLayout(chartCard);
    chartLayout->setContentsMargins(20, 20, 20, 20);
    
    // Chart Header
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
    
    // Legend & Selector
    auto* legend = new QHBoxLayout;
    
    auto* createPill = [](const QString& labelText, const QString& color) {
        auto* pill = new QFrame;
        pill->setStyleSheet("background-color: #0f172a; border-radius: 6px;");
        auto* pl = new QHBoxLayout(pill);
        pl->setContentsMargins(10, 5, 10, 5);
        auto* dot = new QLabel("●");
        dot->setStyleSheet(QString("color: %1; font-size: 10px;").arg(color));
        auto* txt = new QLabel(labelText);
        txt->setStyleSheet("color: #e2e8f0; font-size: 11px;");
        pl->addWidget(dot);
        pl->addWidget(txt);
        return pill;
    };
    
    legend->addWidget(createPill("Revenue", "#3b82f6"));
    legend->addWidget(createPill("Target", "#64748b"));
    legend->addSpacing(20);
    
    // Chart Instance
    auto* lineChart = new LineChart;
    
    // Period Selector (Moved to LineChart.cpp)
    auto* periodCombo = lineChart->createPeriodSelector(chartTitle);
    legend->addWidget(periodCombo);
    
    chartHeader->addLayout(legend);
    chartLayout->addLayout(chartHeader);
    chartLayout->addWidget(lineChart);
    
    leftLayout->addWidget(chartCard, 2);
    
    // --- 3. RECENT ORDERS TABLE ---
    // File: ../Components/OverviewPage/RecentOrdersTable.h/cpp
    recentOrdersTable = new RecentOrdersTable(this);
    leftLayout->addWidget(recentOrdersTable, 0); 
    
    // =========================================================================
    // RIGHT COLUMN (Calendar, Stats)
    // =========================================================================
    auto* rightCol = new QWidget;
    rightCol->setFixedWidth(310);
    auto* rightLayout = new QVBoxLayout(rightCol);
    rightLayout->setSpacing(25);

    // --- 4. MINI CALENDAR ---
    // File: ../Components/OverviewPage/MiniCalendar.h/cpp
    mainCalendar = new MiniCalendar;
    rightLayout->addWidget(mainCalendar);

    // --- 5. ORDER STATUS BARCHART ---
    // File: ../Components/OverviewPage/StatusBarChart.h/cpp
    auto* statsCard = new QFrame;
    statsCard->setFixedSize(300, 330);
    statsCard->setStyleSheet("background-color: #1e293b; border-radius: 12px; border: 1px solid #334155;");
    auto* statsLayout = new QVBoxLayout(statsCard);
    statsLayout->setContentsMargins(0, 0, 0, 0);

    mainStatusBarChart = new StatusBarChart;
    statsLayout->addWidget(mainStatusBarChart);
    
    rightLayout->addWidget(statsCard);
    rightLayout->addStretch();

    // FINALIZE LAYOUT
    contentLayout->addWidget(leftCol, 3);
    contentLayout->addWidget(rightCol, 1);
    
    scrollArea->setWidget(contentArea);
    overviewLayout->addWidget(scrollArea);
}



