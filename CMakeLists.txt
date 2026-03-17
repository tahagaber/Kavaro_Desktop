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
    src/Screens/Dashboard/Components/TopNavbar.cpp
    src/Screens/Dashboard/Components/Sidebar.cpp
    src/Screens/Dashboard/Pages/OverviewPage.cpp
    src/Screens/Dashboard/Pages/AllOrdersPage.cpp
    src/Screens/Dashboard/Pages/STLUploadsPage.cpp
)

target_include_directories(FinancialDashboard PRIVATE
    src/Screens/Dashboard
    src/Screens/Dashboard/Components
    src/Screens/Dashboard/Components/OverviewPage
    src/Screens/Dashboard/Pages
    src/Auth/login
)

target_link_libraries(FinancialDashboard
    Qt6::Core
    Qt6::Widgets
)