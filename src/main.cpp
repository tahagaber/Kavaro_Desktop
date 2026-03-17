#include <QApplication>
#include "FinancialDashboard.h"
#include "login.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Global font
    QFont font("Segoe UI", 10);
    app.setFont(font);
    
    FinancialDashboard* dashboard = new FinancialDashboard();
    LoginWindow* login = new LoginWindow();
    
    // Transition mechanism
    QObject::connect(login, &LoginWindow::loginSuccessful, [&]() {
        login->close();
        dashboard->showMaximized();
    });

    
    login->show();
    
    int result = app.exec();
    
    delete login;
    delete dashboard;
    
    return result;
}
