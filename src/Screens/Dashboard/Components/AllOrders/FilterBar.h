#pragma once
#include <QWidget>

class QLineEdit;
class QComboBox;
class QPushButton;

class FilterBar : public QWidget {
    Q_OBJECT
public:
    explicit FilterBar(QWidget* parent = nullptr);
    QString currentSearch() const;
    QString currentStatus() const;

private:
    QLineEdit* searchInput;
    QComboBox* categoryCombo;
    QComboBox* statusCombo;
    QPushButton* filterBtn;
    QPushButton* addOrderBtn;

signals:
    void addOrderRequested();
    void searchChanged(const QString& text);
    void filterChanged(const QString& category, const QString& status);
};
