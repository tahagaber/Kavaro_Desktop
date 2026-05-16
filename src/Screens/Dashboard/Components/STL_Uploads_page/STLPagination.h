#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class STLPagination : public QWidget {
    Q_OBJECT
public:
    explicit STLPagination(int currentPage, int totalPages, QWidget* parent = nullptr);
};
