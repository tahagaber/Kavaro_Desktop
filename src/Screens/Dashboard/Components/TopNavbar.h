#pragma once
#include <QFrame>

class TopNavbar : public QFrame {
    Q_OBJECT
public:
    explicit TopNavbar(QWidget* parent = nullptr);

signals:
    void toggleSidebarClicked();
};
