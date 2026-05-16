#pragma once
#include <QWidget>
#include <QScrollArea>
#include "../Components/STL_Uploads_page/STLGrid.h"

class STLUploadsPage : public QWidget {
    Q_OBJECT
public:
    explicit STLUploadsPage(QWidget* parent = nullptr);

private slots:
    void addNewCard(const QString& name, const QString& details, const QString& category, const QString& imagePath);

private:
    QScrollArea* scrollArea;
    STLGrid* stlGrid;
};
