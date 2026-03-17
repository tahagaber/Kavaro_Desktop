#include "MiniCalendar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLocale>

MiniCalendar::MiniCalendar(QWidget* parent) : QFrame(parent) {
    currentDisplayDate = QDate::currentDate();
    
    setFixedSize(300, 330); // Unified size
    setStyleSheet(R"(
        MiniCalendar {
            background-color: #1e293b;
            border-radius: 12px;
            border: 1px solid #334155;
        }
    )");

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    // Header: Month Year + Arrows
    auto* header = new QHBoxLayout;
    
    monthLabel = new QLabel;
    monthLabel->setStyleSheet("color: white; font-size: 15px; font-weight: bold;");
    header->addWidget(monthLabel);
    
    header->addStretch();

    auto* prevBtn = new QPushButton("<");
    auto* nextBtn = new QPushButton(">");
    QString arrowStyle = R"(
        QPushButton {
            background: transparent;
            color: #94a3b8;
            border: none;
            font-size: 16px;
            font-weight: bold;
        }
        QPushButton:hover { color: white; }
    )";
    prevBtn->setStyleSheet(arrowStyle);
    nextBtn->setStyleSheet(arrowStyle);
    prevBtn->setCursor(Qt::PointingHandCursor);
    nextBtn->setCursor(Qt::PointingHandCursor);

    header->addWidget(prevBtn);
    header->addWidget(nextBtn);
    mainLayout->addLayout(header);

    // Day Headers (S M T W T F S)
    auto* dayHeaders = new QHBoxLayout;
    QStringList days = {"S", "M", "T", "W", "T", "F", "S"};
    for(const QString& day : days) {
        auto* l = new QLabel(day);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("color: #64748b; font-size: 11px; font-weight: bold;");
        dayHeaders->addWidget(l);
    }
    mainLayout->addLayout(dayHeaders);

    // Days Grid
    daysGrid = new QGridLayout;
    daysGrid->setSpacing(5);
    mainLayout->addLayout(daysGrid);

    connect(prevBtn, &QPushButton::clicked, this, &MiniCalendar::prevMonth);
    connect(nextBtn, &QPushButton::clicked, this, &MiniCalendar::nextMonth);

    updateCalendar();
}

void MiniCalendar::updateCalendar() {
    // Clear existing labels
    QLayoutItem *child;
    while ((child = daysGrid->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    monthLabel->setText(currentDisplayDate.toString("MMMM yyyy").toUpper());

    QDate firstDay(currentDisplayDate.year(), currentDisplayDate.month(), 1);
    int dayOfWeek = firstDay.dayOfWeek(); // 1=Mon, 7=Sun
    if (dayOfWeek == 7) dayOfWeek = 0; // Adjust for Sunday start: 0=Sun, 1=Mon...
    
    int daysInMonth = currentDisplayDate.daysInMonth();
    QDate today = QDate::currentDate();

    int row = 0;
    int col = dayOfWeek;

    for (int i = 1; i <= daysInMonth; ++i) {
        auto* dayLabel = new QLabel(QString::number(i));
        dayLabel->setFixedSize(32, 32);
        dayLabel->setAlignment(Qt::AlignCenter);
        
        bool isToday = (today.year() == currentDisplayDate.year() && 
                        today.month() == currentDisplayDate.month() && 
                        today.day() == i);

        if (isToday) {
            dayLabel->setStyleSheet(R"(
                background-color: #3b82f6;
                color: white;
                border-radius: 16px;
                font-weight: bold;
            )");
        } else {
            dayLabel->setStyleSheet("color: #e2e8f0; font-size: 13px;");
        }

        daysGrid->addWidget(dayLabel, row, col);
        
        col++;
        if (col > 6) {
            col = 0;
            row++;
        }
    }
}

void MiniCalendar::nextMonth() {
    currentDisplayDate = currentDisplayDate.addMonths(1);
    updateCalendar();
}

void MiniCalendar::prevMonth() {
    currentDisplayDate = currentDisplayDate.addMonths(-1);
    updateCalendar();
}
