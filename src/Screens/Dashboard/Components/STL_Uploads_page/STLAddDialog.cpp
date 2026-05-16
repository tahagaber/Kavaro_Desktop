#include "STLAddDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>

STLAddDialog::STLAddDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Add New STL Model");
    setFixedWidth(500);
    setStyleSheet("background-color: #0f172a; border-radius: 12px;");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    auto* title = new QLabel("Upload New Project");
    title->setStyleSheet("font-size: 24px; font-weight: 800; color: #f8fafc; font-family: 'Outfit', sans-serif;");
    layout->addWidget(title);

    auto createInput = [&](const QString& label, const QString& placeholder, QWidget* widget) {
        auto* container = new QVBoxLayout;
        container->setSpacing(8);
        auto* l = new QLabel(label);
        l->setStyleSheet("color: #64748b; font-size: 13px; font-weight: 700; text-transform: uppercase; letter-spacing: 0.5px;");
        
        if (auto* edit = qobject_cast<QLineEdit*>(widget)) {
            edit->setPlaceholderText(placeholder);
            edit->setFixedHeight(45);
            edit->setStyleSheet(R"(
                QLineEdit {
                    background: #1e293b;
                    border: 1px solid #334155;
                    border-radius: 10px;
                    padding: 0 15px;
                    color: white;
                    font-size: 14px;
                }
                QLineEdit:focus { border-color: #3b82f6; background: #0f172a; }
            )");
            container->addWidget(l);
            container->addWidget(edit);
        } else if (auto* combo = qobject_cast<QComboBox*>(widget)) {
            combo->setFixedHeight(45);
            combo->setStyleSheet(R"(
                QComboBox {
                    background: #1e293b;
                    border: 1px solid #334155;
                    border-radius: 10px;
                    padding: 0 15px;
                    color: white;
                    font-size: 14px;
                }
                QComboBox::drop-down { border: none; }
            )");
            container->addWidget(l);
            container->addWidget(combo);
        }
        layout->addLayout(container);
    };

    nameEdit = new QLineEdit;
    createInput("Model Name", "e.g. Cyber_Helmet_V1.stl", nameEdit);
    
    sizeEdit = new QLineEdit;
    createInput("Model Details", "e.g. 24MB, 1.2M Triangles", sizeEdit);

    categoryCombo = new QComboBox;
    categoryCombo->addItems({"Gaming", "Anime", "Office Ornaments"});
    createInput("Classification", "", categoryCombo);

    auto* fileRow = new QHBoxLayout;
    fileRow->setSpacing(10);
    
    auto createPickerBtn = [](const QString& text) {
        auto* btn = new QPushButton(text);
        btn->setFixedHeight(45);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(R"(
            QPushButton {
                background: #1e293b;
                border: 1px solid #334155;
                color: #cbd5e1;
                border-radius: 10px;
                font-weight: 600;
            }
            QPushButton:hover { background: #334155; color: white; }
        )");
        return btn;
    };
    
    selectFileBtn = createPickerBtn("📎 PICK STL FILE");
    selectImageBtn = createPickerBtn("🖼 PICK THUMBNAIL");
    
    connect(selectFileBtn, &QPushButton::clicked, this, []() {
        QFileDialog::getOpenFileName(nullptr, "Select STL File", "", "STL Files (*.stl);;All Files (*)");
    });
    
    connect(selectImageBtn, &QPushButton::clicked, this, [this]() {
        pickedImagePath = QFileDialog::getOpenFileName(nullptr, "Select Thumbnail", "", "Images (*.png *.jpg *.jpeg)");
        if (!pickedImagePath.isEmpty()) {
            selectImageBtn->setText("✅ IMAGE LOADED");
        }
    });

    fileRow->addWidget(selectFileBtn, 1);
    fileRow->addWidget(selectImageBtn, 1);
    layout->addLayout(fileRow);

    auto* saveBtn = new QPushButton("🚀 START UPLOAD");
    saveBtn->setFixedHeight(54);
    saveBtn->setCursor(Qt::PointingHandCursor);
    saveBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border-radius: 12px;
            font-size: 16px;
            font-weight: 800;
            border: none;
            margin-top: 20px;
        }
        QPushButton:hover { background-color: #2563eb; }
    )");
    
    connect(saveBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(saveBtn);
}

QString STLAddDialog::getModelName() const { return nameEdit->text(); }
QString STLAddDialog::getModelDetails() const { return sizeEdit->text(); }
QString STLAddDialog::getCategory() const { return categoryCombo->currentText(); }
QString STLAddDialog::getImagePath() const { return pickedImagePath; }
