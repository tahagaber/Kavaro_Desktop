#pragma once
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

class SettingsCard : public QFrame {
    Q_OBJECT
public:
    explicit SettingsCard(const QString& title, QWidget* parent = nullptr);
    void setContent(QLayout* layout);

private:
    QVBoxLayout* m_contentLayout;
};
