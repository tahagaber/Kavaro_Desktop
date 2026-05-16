#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

class STLUploadArea : public QWidget {
    Q_OBJECT
public:
    explicit STLUploadArea(QWidget* parent = nullptr);

signals:
    void stlAdded(const QString& name, const QString& details, const QString& category, const QString& imagePath);

private slots:
    void handleUploadClick();
};
