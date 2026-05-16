#include "AccessMetrics.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>

AccessMetrics::AccessMetrics(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* card = new SettingsCard("System Status", this);
    auto* content = new QVBoxLayout();
    content->setSpacing(15);

    // Live Clock Section
    auto* clockContainer = new QVBoxLayout();
    clockContainer->setSpacing(2);
    
    auto* clockTitle = new QLabel("CURRENT SYSTEM TIME");
    clockTitle->setStyleSheet("color: #64748b; font-size: 10px; font-weight: 800; letter-spacing: 1px;");
    clockContainer->addWidget(clockTitle);

    m_timeLabel = new QLabel();
    m_timeLabel->setStyleSheet("color: #f1f5f9; font-size: 28px; font-weight: 800; font-family: 'Consolas', 'Monospace';");
    clockContainer->addWidget(m_timeLabel);
    
    auto* dateLabel = new QLabel(QDateTime::currentDateTime().toString("dddd, MMMM d, yyyy"));
    dateLabel->setStyleSheet("color: #94a3b8; font-size: 12px; font-weight: 500;");
    clockContainer->addWidget(dateLabel);
    
    content->addLayout(clockContainer);
    content->addSpacing(10);

    // Separator
    auto* line = new QFrame();
    line->setFixedHeight(1);
    line->setStyleSheet("background-color: #1e293b;");
    content->addWidget(line);
    content->addSpacing(5);

    auto addStat = [&](const QString& label, const QString& value, const QString& color = "#f1f5f9") {
        auto* row = new QHBoxLayout();
        auto* lbl = new QLabel(label);
        lbl->setStyleSheet("color: #64748b; font-size: 11px; font-weight: 600;");
        auto* val = new QLabel(value);
        val->setStyleSheet("color: " + color + "; font-size: 11px; font-weight: 700;");
        row->addWidget(lbl);
        row->addStretch();
        row->addWidget(val);
        content->addLayout(row);
    };

    addStat("Version", "2.4.0-STABLE");
    addStat("Sync Status", "Synchronized", "#10b981");

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AccessMetrics::updateTime);
    m_timer->start(1000);
    updateTime();

    card->setContent(content);
    mainLayout->addWidget(card);
}

void AccessMetrics::updateTime() {
    m_timeLabel->setText(QDateTime::currentDateTime().toString("HH:mm:ss"));
}
