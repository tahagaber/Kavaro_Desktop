#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class STLAddDialog : public QDialog {
    Q_OBJECT
public:
    explicit STLAddDialog(QWidget* parent = nullptr);
    
    QString getModelName() const;
    QString getModelDetails() const;
    QString getCategory() const;
    QString getImagePath() const;

private:
    QLineEdit* nameEdit;
    QLineEdit* sizeEdit;
    QComboBox* categoryCombo;
    QPushButton* selectFileBtn;
    QPushButton* selectImageBtn;
    QString pickedImagePath;
};
