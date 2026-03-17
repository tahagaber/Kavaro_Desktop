#pragma once
#include <QFrame>

class QButtonGroup;

class Sidebar : public QFrame {
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);

public slots:
    void toggleExpanded();

signals:
    void pageSelected(int id);

private:
    QButtonGroup* sidebarGroup;
    bool isSidebarVisible = true;
};
