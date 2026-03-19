#include "FilterBar.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

FilterBar::FilterBar(QWidget* parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(15);

    // Search Input
    searchInput = new QLineEdit;
    searchInput->setPlaceholderText(QString::fromUtf8("\U0001F50D Search models by name, tag, or material..."));
    searchInput->setFixedHeight(45);
    searchInput->setStyleSheet(R"(
        QLineEdit {
            background-color: #1e2433;
            color: #f8fafc;
            border-radius: 8px;
            padding: 0 15px;
            border: 1px solid #283548;
            font-size: 14px;
        }
        QLineEdit:focus { border: 1px solid #3b82f6; background-color: #0f172a; }
    )");
    connect(searchInput, &QLineEdit::textChanged, this, &FilterBar::searchChanged);
    layout->addWidget(searchInput, 1); // stretch factor 1

    // Category ComboBox
    categoryCombo = new QComboBox;
    categoryCombo->addItems({"Category: All", "Industrial", "Dental", "Art"});
    categoryCombo->setFixedHeight(45);
    categoryCombo->setFixedWidth(160);
    QString comboStyle = R"(
        QComboBox {
            background-color: #1e2433;
            color: #e2e8f0;
            border-radius: 8px;
            padding: 0 15px;
            border: 1px solid #283548;
            font-size: 14px;
        }
        QComboBox::drop-down { border: none; }
        QComboBox QAbstractItemView {
            background-color: #1a2332;
            color: #e2e8f0;
            selection-background-color: #3b82f6;
            border: 1px solid #283548;
        }
    )";
    categoryCombo->setStyleSheet(comboStyle);
    layout->addWidget(categoryCombo);

    // Status ComboBox
    statusCombo = new QComboBox;
    statusCombo->addItems({"Status: All", "Printing", "Painting", "Review", "Delivered", "Returned"});
    statusCombo->setFixedHeight(45);
    statusCombo->setFixedWidth(160);
    statusCombo->setStyleSheet(comboStyle);
    
    auto emitFilter = [this]() {
        emit filterChanged(categoryCombo->currentText(), statusCombo->currentText());
    };
    connect(categoryCombo, &QComboBox::currentTextChanged, emitFilter);
    connect(statusCombo, &QComboBox::currentTextChanged, emitFilter);

    layout->addWidget(statusCombo);

    // Filter Menu Button
    filterBtn = new QPushButton(QString::fromUtf8("\u2630")); // Hamburger/Filter icon replacement
    filterBtn->setFixedSize(45, 45);
    filterBtn->setCursor(Qt::PointingHandCursor);
    filterBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #1e2433;
            color: #94a3b8;
            border-radius: 8px;
            border: 1px solid #283548;
            font-size: 18px;
        }
        QPushButton:hover { background-color: #2a374a; color: white; }
    )");
    layout->addWidget(filterBtn);

    // Add Order Button
    addOrderBtn = new QPushButton("+ Add Order");
    addOrderBtn->setFixedHeight(45);
    addOrderBtn->setCursor(Qt::PointingHandCursor);
    addOrderBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 8px;
            font-size: 14px;
            font-weight: bold;
            padding: 0 20px;
        }
        QPushButton:hover { background-color: #2563eb; }
    )");
    connect(addOrderBtn, &QPushButton::clicked, this, &FilterBar::addOrderRequested);
    layout->addWidget(addOrderBtn);
}

QString FilterBar::currentSearch() const {
    return searchInput->text();
}

QString FilterBar::currentStatus() const {
    return statusCombo->currentText();
}
