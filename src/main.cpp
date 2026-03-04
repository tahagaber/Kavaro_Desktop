#include <QApplication>
#include "FinancialDashboard.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Global font
    QFont font("Segoe UI", 10);
    app.setFont(font);
    
    FinancialDashboard window;
    window.show();
    
    return app.exec();
}
