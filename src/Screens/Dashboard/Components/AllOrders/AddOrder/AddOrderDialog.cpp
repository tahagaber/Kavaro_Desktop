#include "AddOrderDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

AddOrderDialog::AddOrderDialog(QWidget* parent) : QDialog(parent) {
    setupUI();
}

void AddOrderDialog::setupUI() {
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(550, 780);

    auto* container = new QFrame(this);
    container->setObjectName("MainContainer");
    container->setFixedSize(550, 780);
    container->setStyleSheet(R"(
        #MainContainer {
            background-color: #0f172a;
            border: 1px solid #1e293b;
            border-radius: 24px;
        }
    )");

    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(40);
    shadow->setColor(QColor(0, 0, 0, 150));
    shadow->setOffset(0, 10);
    container->setGraphicsEffect(shadow);

    auto* mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- Header Section with Gradient ---
    auto* header = new QFrame;
    header->setFixedHeight(120);
    header->setStyleSheet(R"(
        QFrame {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2563eb, stop:1 #7c3aed);
            border-top-left-radius: 24px;
            border-top-right-radius: 24px;
        }
    )");
    auto* headerLay = new QHBoxLayout(header);
    headerLay->setContentsMargins(40, 0, 30, 0);

    auto* titleContainer = new QVBoxLayout;
    auto* title = new QLabel("Order Management");
    title->setStyleSheet("color: white; font-size: 26px; font-weight: 900; border: none; background: transparent;");
    auto* subtitle = new QLabel("Update or create a new order ticket");
    subtitle->setStyleSheet("color: rgba(255, 255, 255, 0.7); font-size: 13px; border: none; background: transparent;");
    titleContainer->addStretch();
    titleContainer->addWidget(title);
    titleContainer->addWidget(subtitle);
    titleContainer->addStretch();

    auto* closeBtn = new QPushButton("\u2715");
    closeBtn->setFixedSize(36, 36);
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setStyleSheet(R"(
        QPushButton { 
            background-color: rgba(255, 255, 255, 0.15); 
            color: white; 
            border-radius: 18px; 
            font-size: 16px; 
            font-weight: 800; 
            border: none;
        }
        QPushButton:hover { background-color: #ef4444; color: white; }
    )");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::reject);

    headerLay->addLayout(titleContainer);
    headerLay->addStretch();
    headerLay->addWidget(closeBtn);
    mainLayout->addWidget(header);

    // --- Content Section ---
    auto* content = new QFrame;
    auto* contentLay = new QVBoxLayout(content);
    contentLay->setContentsMargins(40, 30, 40, 30);
    contentLay->setSpacing(18);

    QString inputStyle = R"(
        QLineEdit, QComboBox { 
            background-color: #1e293b; 
            color: #f8fafc; 
            padding: 12px 16px; 
            border-radius: 10px; 
            border: 1px solid transparent; 
            font-size: 15px;
        }
        QLineEdit:focus, QComboBox:focus { 
            border: 1px solid #3b82f6; 
            background-color: #0f172a; 
        }
        QComboBox::drop-down { border: none; width: 30px; }
        QComboBox::down-arrow { image: none; border-left: 5px solid transparent; border-right: 5px solid transparent; border-top: 5px solid #94a3b8; margin-right: 15px; }
        
        QComboBox QAbstractItemView {
            background-color: #2d457bff;
            color: #f8fafc;
            selection-background-color: #2563eb;
            selection-color: white;
            outline: none;
            border: 1px solid #334155;
            border-radius: 10px;
            padding: 10px;
        }
    )";
    QString labelStyle = "color: #64748b; font-size: 11px; font-weight: 800; text-transform: uppercase; letter-spacing: 1.2px;";

    auto createFormField = [&](const QString& icon, const QString& label, QWidget* widget) {
        auto* box = new QVBoxLayout;
        box->setSpacing(6);
        auto* lbl = new QLabel(icon + " " + label);
        lbl->setStyleSheet(labelStyle);
        box->addWidget(lbl);
        widget->setStyleSheet(inputStyle);
        box->addWidget(widget);
        contentLay->addLayout(box);
    };

    nameInput = new QLineEdit;
    nameInput->setPlaceholderText("Customer name...");
    createFormField(QString::fromUtf8("\U0001F464"), "Client Identity", nameInput);

    phoneInput = new QLineEdit;
    phoneInput->setPlaceholderText("01xxxxxxxxx");
    createFormField(QString::fromUtf8("\U0001F4DE"), "Primary Contact", phoneInput);

    addressInput = new QLineEdit;
    addressInput->setPlaceholderText("Shipping address...");
    createFormField(QString::fromUtf8("\U0001F4CD"), "Delivery location", addressInput);

    // Row 1: Product & Size
    auto* row1 = new QHBoxLayout;
    row1->setSpacing(15);
    
    auto* pBox = new QVBoxLayout;
    pBox->setSpacing(6);
    auto* pLbl = new QLabel(QString::fromUtf8("\U0001F4E6") + " Product");
    pLbl->setStyleSheet(labelStyle);
    productInput = new QLineEdit;
    productInput->setStyleSheet(inputStyle);
    pBox->addWidget(pLbl);
    pBox->addWidget(productInput);
    
    auto* sBox = new QVBoxLayout;
    sBox->setSpacing(6);
    auto* sLbl = new QLabel(QString::fromUtf8("\U0001F4CF") + " Size");
    sLbl->setStyleSheet(labelStyle);
    sizeCombo = new QComboBox;
    for(int i = 8; i <= 15; ++i) sizeCombo->addItem(QString::number(i) + " cm");
    sizeCombo->setStyleSheet(inputStyle);
    sBox->addWidget(sLbl);
    sBox->addWidget(sizeCombo);
    
    row1->addLayout(pBox, 2);
    row1->addLayout(sBox, 1);
    contentLay->addLayout(row1);

    // Row 2: Status Selection
    auto* statusBox = new QVBoxLayout;
    statusBox->setSpacing(6);
    auto* statusLbl = new QLabel(QString::fromUtf8("\U0001F3AF") + " Current Status");
    statusLbl->setStyleSheet(labelStyle);
    statusCombo = new QComboBox;
    statusCombo->addItems({"Review", "Printing", "Painting", "Delivered", "Returned"});
    statusCombo->setStyleSheet(inputStyle);
    statusBox->addWidget(statusLbl);
    statusBox->addWidget(statusCombo);
    contentLay->addLayout(statusBox);

    paintCheck = new QCheckBox(" Add expert hand-painting service");
    paintCheck->setCursor(Qt::PointingHandCursor);
    paintCheck->setStyleSheet(R"(
        QCheckBox { color: #94a3b8; font-size: 13px; font-weight: 500; padding: 5px 0; border: none; }
        QCheckBox::indicator { width: 20px; height: 20px; border-radius: 5px; border: 1px solid #334155; background: #1e293b; }
        QCheckBox::indicator:checked { background: #3b82f6; border-color: #3b82f6; }
    )");
    contentLay->addWidget(paintCheck);

    contentLay->addStretch();

    // --- Footer ---
    auto* footer = new QHBoxLayout;
    footer->setSpacing(15);
    
    auto* cancelBtn = new QPushButton("Discard");
    cancelBtn->setFixedHeight(50);
    cancelBtn->setStyleSheet(R"(
        QPushButton { background: #1e293b; color: #94a3b8; border-radius: 12px; font-weight: 700; border: none; }
        QPushButton:hover { background: #334155; color: white; }
    )");
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

    auto* saveBtn = new QPushButton("Save Order Information");
    saveBtn->setFixedHeight(50);
    saveBtn->setStyleSheet(R"(
        QPushButton { background: #3b82f6; color: white; border-radius: 12px; font-weight: 700; border: none; }
        QPushButton:hover { background: #2563eb; }
    )");
    connect(saveBtn, &QPushButton::clicked, this, &QDialog::accept);

    footer->addWidget(cancelBtn, 1);
    footer->addWidget(saveBtn, 2);
    contentLay->addLayout(footer);

    mainLayout->addWidget(content);
}

void AddOrderDialog::setFormData(const OrderFormData& data) {
    nameInput->setText(data.clientName);
    phoneInput->setText(data.phone);
    addressInput->setText(data.address);
    productInput->setText(data.product);
    sizeCombo->setCurrentText(data.size);
    statusCombo->setCurrentText(data.status);
    paintCheck->setChecked(data.isPainted);
}

OrderFormData AddOrderDialog::getFormData() const {
    return {
        nameInput->text().trimmed(),
        phoneInput->text().trimmed(),
        addressInput->text().trimmed(),
        productInput->text().trimmed(),
        sizeCombo->currentText(),
        paintCheck->isChecked(),
        statusCombo->currentText()
    };
}
