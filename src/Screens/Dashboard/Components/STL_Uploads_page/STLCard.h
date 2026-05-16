#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

class STLCard : public QWidget {
    Q_OBJECT
public:
    explicit STLCard(const QString& title, const QString& imagePath, const QString& status, 
                    const QString& size, const QString& triangles, const QString& date, 
                    QWidget* parent = nullptr);
};
