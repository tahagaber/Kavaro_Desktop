#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>

class STLCategoryTabs : public QWidget {
    Q_OBJECT
public:
    explicit STLCategoryTabs(QWidget* parent = nullptr);

signals:
    void categorySelected(const QString& category);

private slots:
    void handleTabClick();

private:
    QVector<QPushButton*> tabs;
    void updateTabStyles(QPushButton* activeTab);
};
