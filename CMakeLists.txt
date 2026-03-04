cmake_minimum_required(VERSION 3.16)
project(FinancialDashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(FinancialDashboard
    src/main.cpp
    src/FinancialDashboard.cpp
)

target_link_libraries(FinancialDashboard
    Qt6::Core
    Qt6::Widgets
)