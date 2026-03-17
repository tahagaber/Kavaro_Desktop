#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QCheckBox>
#include <QToolButton>
#include <QTimer>
#include <QProgressBar>

class LoginWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void handleLogin();
    void togglePasswordVisibility();
    void validateEmail(const QString& text);
    void checkPasswordStrength(const QString& text);
    void finishLogin();

private:
    void showError(const QString& message);
    void clearError();

    QLineEdit* emailField;
    QLineEdit* passwordField;
    QPushButton* loginBtn;
    QLabel* errorLabel;
    
    QToolButton* togglePwdBtn;
    QProgressBar* pwdStrengthBar;
    QCheckBox* rememberMeCb;
    QLabel* forgotPwdLabel;
    
    QTimer* loginTimer;

    const QString normalInputStyle = R"(
        QLineEdit {
            background-color: #1e293b;
            border: 1px solid #334155;
            border-radius: 10px;
            padding: 0 40px 0 20px;
            color: #f8fafc;
            font-size: 15px;
        }
        QLineEdit:focus {
            border: 1px solid #3b82f6;
            background-color: #0f172a;
        }
    )";
    
    const QString errorInputStyle = R"(
        QLineEdit {
            background-color: #1e293b;
            border: 1px solid #ef4444;
            border-radius: 10px;
            padding: 0 40px 0 20px;
            color: #f8fafc;
            font-size: 15px;
        }
        QLineEdit:focus {
            border: 1px solid #ef4444;
            background-color: #0f172a;
        }
    )";
};
