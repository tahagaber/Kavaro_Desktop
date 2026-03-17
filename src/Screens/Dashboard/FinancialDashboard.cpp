#include "FinancialDashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Components/TopNavbar.h"
#include "Components/Sidebar.h"
#include "Pages/OverviewPage.h"
#include "Pages/AllOrdersPage.h"
#include "Pages/STLUploadsPage.h"

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
    
    // Components Setup
    auto* navbar = new TopNavbar(this);
    mainLayout->addWidget(navbar);
    
    auto* bodyWidget = new QWidget;
    auto* bodyLayout = new QHBoxLayout(bodyWidget);
    bodyLayout->setContentsMargins(0, 0, 0, 0);
    bodyLayout->setSpacing(0);
    mainLayout->addWidget(bodyWidget, 1);
    
    auto* sidebar = new Sidebar(this);
    bodyLayout->addWidget(sidebar);

    // Context Stack Setup
    mainContentStack = new QStackedWidget;
    bodyLayout->addWidget(mainContentStack, 1);

    // Add Pages to Stack
    mainContentStack->addWidget(new OverviewPage);
    mainContentStack->addWidget(new AllOrdersPage);
    mainContentStack->addWidget(new STLUploadsPage);
    
    // Mock pages for Revenue & Burn
    auto* revenueLabel = new QLabel("Revenue Analytics Coming Soon...");
    revenueLabel->setStyleSheet("color: white; font-size: 20px; font-weight: bold; padding: 40px;");
    mainContentStack->addWidget(revenueLabel);
    
    auto* burnLabel = new QLabel("Burn Rate Analytics Coming Soon...");
    burnLabel->setStyleSheet("color: white; font-size: 20px; font-weight: bold; padding: 40px;");
    mainContentStack->addWidget(burnLabel);

    // Wiring Components Together
    connect(navbar, &TopNavbar::toggleSidebarClicked, sidebar, &Sidebar::toggleExpanded);
    connect(sidebar, &Sidebar::pageSelected, mainContentStack, &QStackedWidget::setCurrentIndex);
}
