cmake_minimum_required(VERSION 3.16)
project(FinancialDashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(FinancialDashboard
    src/main.cpp
    src/Auth/login/login.cpp
    src/Screens/Dashboard/FinancialDashboard.cpp
    src/Screens/Dashboard/Components/OverviewPage/LineChart.cpp
    src/Screens/Dashboard/Components/OverviewPage/OrderStatusChart.cpp
    src/Screens/Dashboard/Components/OverviewPage/MetricCard.cpp
    src/Screens/Dashboard/Components/OverviewPage/MiniCalendar.cpp
    src/Screens/Dashboard/Components/OverviewPage/StatusBarChart.cpp
    src/Screens/Dashboard/Components/OverviewPage/RecentOrdersTable.cpp
    src/Screens/Dashboard/Components/AllOrders/FilterBar.cpp
    src/Screens/Dashboard/Components/AllOrders/OrderTable.cpp
    src/Screens/Dashboard/Components/AllOrders/PaginationBar.cpp
    src/Screens/Dashboard/Components/AllOrders/AddOrder/AddOrderDialog.cpp
    src/Screens/Dashboard/Components/TopNavbar.cpp
    src/Screens/Dashboard/Components/Sidebar.cpp
    src/Screens/Dashboard/Pages/OverviewPage.cpp
    src/Screens/Dashboard/Pages/AllOrdersPage.cpp
    src/Screens/Dashboard/Pages/STLUploadsPage.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLHeader.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLCategoryTabs.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLUploadArea.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLCard.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLGrid.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLPagination.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLAddDialog.cpp
    src/Screens/Dashboard/Components/STL_Uploads_page/STLHeader.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLCategoryTabs.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLUploadArea.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLCard.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLGrid.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLPagination.h
    src/Screens/Dashboard/Components/STL_Uploads_page/STLAddDialog.h
    src/Screens/Dashboard/Pages/NotificationsPage.cpp
    src/Screens/Dashboard/Pages/NotificationsPage.h
    src/Screens/Dashboard/Pages/SettingsPage.cpp
    src/Screens/Dashboard/Pages/SettingsPage.h
    src/Screens/Dashboard/Components/notifcations/NotificationsHeader.cpp
    src/Screens/Dashboard/Components/notifcations/NotificationsHeader.h
    src/Screens/Dashboard/Components/notifcations/NotificationsSidebar.cpp
    src/Screens/Dashboard/Components/notifcations/NotificationsSidebar.h
    src/Screens/Dashboard/Components/notifcations/NotificationCard.cpp
    src/Screens/Dashboard/Components/notifcations/NotificationCard.h
    src/Screens/Dashboard/Components/notifcations/NotificationsList.cpp
    src/Screens/Dashboard/Components/notifcations/NotificationsList.h
)

target_include_directories(FinancialDashboard PRIVATE
    src/Screens/Dashboard
    src/Screens/Dashboard/Components
    src/Screens/Dashboard/Components/OverviewPage
    src/Screens/Dashboard/Components/AllOrders
    src/Screens/Dashboard/Components/AllOrders/AddOrder
    src/Screens/Dashboard/Components/STL_Uploads_page
    src/Screens/Dashboard/Pages
    src/Auth/login
    src/Screens/Dashboard/Components/notifcations
)

target_link_libraries(FinancialDashboard
    Qt6::Core
    Qt6::Widgets
)