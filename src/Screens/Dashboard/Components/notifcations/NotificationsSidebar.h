#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class NotificationsSidebar : public QWidget {
    Q_OBJECT
public:
    explicit NotificationsSidebar(QWidget* parent = nullptr);

private:
    QWidget* createCategoryButton(const QString& iconText, const QString& titleText, int count, bool isSelected = false);
    QVBoxLayout* buttonsLayout;
};
