#pragma once
#include <QDialog>
#include <QString>

class QLineEdit;
class QComboBox;
class QCheckBox;

struct OrderFormData {
    QString clientName;
    QString phone;
    QString address;
    QString product;
    QString size;
    bool isPainted;
    QString status;
};

class AddOrderDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddOrderDialog(QWidget* parent = nullptr);
    void setFormData(const OrderFormData& data);
    OrderFormData getFormData() const;

private:
    QLineEdit* nameInput;
    QLineEdit* phoneInput;
    QLineEdit* addressInput;
    QLineEdit* productInput;
    QComboBox* sizeCombo;
    QComboBox* statusCombo;
    QCheckBox* paintCheck;
    
    void setupUI();
};
