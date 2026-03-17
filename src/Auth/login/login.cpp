#include "login.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QRegularExpression>
#include <QCursor>
#include <QPropertyAnimation>
#include <QStyle>
#include <QScreen>
#include <QApplication>

LoginWindow::LoginWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Kavaro | Identity Login");
    setFixedSize(1050, 650); 
    
    // Center on screen
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    auto* central = new QWidget;
    central->setStyleSheet("background-color: #0f172a;"); 
    setCentralWidget(central);
    
    auto* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // =====================================
    // LEFT SIDE: IMAGE / BRANDING PANEL
    // =====================================
    auto* leftFrame = new QFrame;
    leftFrame->setFixedWidth(450); 
    leftFrame->setStyleSheet(R"(
        QFrame {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #111827, stop:1 #0b1120);
            border-right: 1px solid #1e293b;
        }
    )");
    
    auto* leftLayout = new QVBoxLayout(leftFrame);
    leftLayout->setContentsMargins(40, 50, 40, 50);
    
    auto* logoLabel = new QLabel("◆ KAVARO");
    logoLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: 800; letter-spacing: 2px; background: transparent;");
    logoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    auto* bigImageLabel = new QLabel;
    QPixmap logoPixmap("D:/Kavaro_decktop/KAVARO.png");
    bigImageLabel->setPixmap(logoPixmap.scaled(350, 350, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bigImageLabel->setAlignment(Qt::AlignCenter);
    bigImageLabel->setStyleSheet("background: transparent;");
    
    auto* brandingText = new QLabel("Welcome to the\nNext Generation of\nFinancial Management.");
    brandingText->setStyleSheet("color: #94a3b8; font-size: 18px; font-weight: 300; line-height: 1.6; background: transparent;");
    brandingText->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    
    leftLayout->addWidget(logoLabel);
    leftLayout->addStretch();
    leftLayout->addWidget(bigImageLabel); 
    leftLayout->addStretch();
    leftLayout->addWidget(brandingText);
    
    mainLayout->addWidget(leftFrame);

    // =====================================
    // RIGHT SIDE: LOGIN FORM
    // =====================================
    auto* rightWidget = new QWidget;
    auto* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(100, 0, 100, 0); 
    rightLayout->setSpacing(35);
    
    auto* formContainer = new QWidget;
    auto* formLayout = new QVBoxLayout(formContainer);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(15); 
    
    // Form Header
    auto* titleLabel = new QLabel("Sign In");
    titleLabel->setStyleSheet("color: #ffffff; font-size: 34px; font-weight: bold; font-family: 'Segoe UI';");
    
    auto* subtitleLabel = new QLabel("Enter your identity credentials to access your dashboard");
    subtitleLabel->setStyleSheet("color: #64748b; font-size: 14px; font-weight: 400; margin-bottom: 20px;");
    
    formLayout->addWidget(titleLabel);
    formLayout->addWidget(subtitleLabel);
    formLayout->addSpacing(10);
    
    // --- EMAIL FIELD ---
    auto* emailLabel = new QLabel("EMAIL ADDRESS");
    emailLabel->setStyleSheet("color: #94a3b8; font-size: 11px; font-weight: 700; letter-spacing: 1px;");
    formLayout->addWidget(emailLabel);
    
    emailField = new QLineEdit;
    emailField->setPlaceholderText("name@kavaro.ai");
    emailField->setFixedHeight(50);
    emailField->setStyleSheet(normalInputStyle);
    formLayout->addWidget(emailField);
    
    connect(emailField, &QLineEdit::textChanged, this, &LoginWindow::validateEmail);

    // --- PASSWORD FIELD ---
    auto* passLabel = new QLabel("PASSWORD");
    passLabel->setStyleSheet("color: #94a3b8; font-size: 11px; font-weight: 700; letter-spacing: 1px;");
    formLayout->addWidget(passLabel);
    
    // Container for password + show/hide button to make it look like a single input
    auto* pwdContainer = new QWidget;
    pwdContainer->setFixedHeight(50);
    pwdContainer->setStyleSheet(R"(
        QWidget#pwdContainer {
            background-color: #1e293b;
            border: 1px solid #334155;
            border-radius: 10px;
        }
        QWidget#pwdContainer[focus="true"] {
            border: 1px solid #3b82f6;
            background-color: #0f172a;
        }
        QWidget#pwdContainer[error="true"] {
            border: 1px solid #ef4444;
        }
    )");
    pwdContainer->setObjectName("pwdContainer");
    
    auto* pwdLayout = new QHBoxLayout(pwdContainer);
    pwdLayout->setContentsMargins(20, 0, 10, 0); // Padding inside the container
    pwdLayout->setSpacing(5);
    
    passwordField = new QLineEdit;
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setPlaceholderText("••••••••••••");
    passwordField->setStyleSheet("QLineEdit { background: transparent; border: none; color: #f8fafc; font-size: 15px; }");
    
    connect(passwordField, &QLineEdit::textChanged, this, &LoginWindow::checkPasswordStrength);

    // Sync focus property to style the parent wrapper
    connect(passwordField, &QLineEdit::textEdited, [pwdContainer, this]() {
        pwdContainer->setProperty("focus", passwordField->hasFocus());
        pwdContainer->style()->unpolish(pwdContainer);
        pwdContainer->style()->polish(pwdContainer);
    });

    // Eye icon button
    togglePwdBtn = new QToolButton;
    togglePwdBtn->setText("👁"); // Basic icon
    togglePwdBtn->setCursor(Qt::PointingHandCursor);
    togglePwdBtn->setStyleSheet(R"(
        QToolButton { 
            background: transparent; 
            border: none; 
            color: #64748b; 
            font-size: 16px; 
            padding-bottom: 2px;
        }
        QToolButton:hover { color: #f8fafc; }
    )");
    
    connect(togglePwdBtn, &QToolButton::clicked, this, &LoginWindow::togglePasswordVisibility);
    
    pwdLayout->addWidget(passwordField);
    pwdLayout->addWidget(togglePwdBtn);
    
    formLayout->addWidget(pwdContainer);
    
    // -- Password Strength Indicator --
    pwdStrengthBar = new QProgressBar;
    pwdStrengthBar->setFixedHeight(4);
    pwdStrengthBar->setTextVisible(false);
    pwdStrengthBar->setRange(0, 100);
    pwdStrengthBar->setValue(0);
    pwdStrengthBar->setStyleSheet(R"(
        QProgressBar { background-color: transparent; border: none; }
        QProgressBar::chunk { background-color: #22c55e; border-radius: 2px; }
    )");
    formLayout->addWidget(pwdStrengthBar);
    
    // --- EXTRAS: REMEMBER ME & FORGOT PASSWORD ---
    auto* extrasLayout = new QHBoxLayout;
    extrasLayout->setContentsMargins(0, 10, 0, 10);
    
    rememberMeCb = new QCheckBox("Remember me");
    rememberMeCb->setCursor(Qt::PointingHandCursor);
    rememberMeCb->setStyleSheet(R"(
        QCheckBox { color: #94a3b8; font-size: 13px; }
        QCheckBox::indicator { width: 18px; height: 18px; background-color: #1e293b; border: 1px solid #334155; border-radius: 4px; }
        QCheckBox::indicator:checked { background-color: #3b82f6; border: 1px solid #3b82f6; image: url(check.png); /* Fallback to color if image fails */ }
        QCheckBox:hover { color: #f8fafc; }
    )");
    
    forgotPwdLabel = new QLabel("<a href='#' style='color: #3b82f6; text-decoration: none; font-size: 13px; font-weight: bold;'>Forgot password?</a>");
    forgotPwdLabel->setTextFormat(Qt::RichText);
    forgotPwdLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    forgotPwdLabel->setOpenExternalLinks(false); // We can handle signals manually if needed
    
    extrasLayout->addWidget(rememberMeCb);
    extrasLayout->addStretch();
    extrasLayout->addWidget(forgotPwdLabel);
    
    formLayout->addLayout(extrasLayout);
    formLayout->addSpacing(10);

    // --- LOGIN BUTTON ---
    loginBtn = new QPushButton("Access Dashboard");
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setFixedHeight(55); 
    loginBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 15px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #2563eb;
        }
        QPushButton:pressed {
            background-color: #1d4ed8;
            padding-top: 2px;
        }
        QPushButton:disabled {
            background-color: #334155;
            color: #64748b;
        }
    )");
    
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(59, 130, 246, 80)); 
    loginBtn->setGraphicsEffect(shadow);
    
    formLayout->addWidget(loginBtn);
    
    // --- ERROR LABEL ---
    errorLabel = new QLabel("");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setStyleSheet("color: #ef4444; font-size: 13px; font-weight: bold; background: rgba(239, 68, 68, 0.1); border-radius: 6px; padding: 10px;");
    errorLabel->hide(); // Hide initially
    
    formLayout->addSpacing(10);
    formLayout->addWidget(errorLabel);
    
    // Center the form container vertically within the right pane
    rightLayout->addStretch();
    rightLayout->addWidget(formContainer);
    rightLayout->addStretch();
    
    mainLayout->addWidget(rightWidget);
    
    // Initialize Timer
    loginTimer = new QTimer(this);
    loginTimer->setSingleShot(true);
    connect(loginTimer, &QTimer::timeout, this, &LoginWindow::finishLogin);
    
    // Connections
    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(passwordField, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);
}

void LoginWindow::togglePasswordVisibility() {
    if (passwordField->echoMode() == QLineEdit::Password) {
        passwordField->setEchoMode(QLineEdit::Normal);
        togglePwdBtn->setText("🙈"); // Or another eye-slash icon
        togglePwdBtn->setStyleSheet("QToolButton { background: transparent; border: none; color: #3b82f6; font-size: 16px; padding-bottom: 2px;}");
    } else {
        passwordField->setEchoMode(QLineEdit::Password);
        togglePwdBtn->setText("👁");
        togglePwdBtn->setStyleSheet("QToolButton { background: transparent; border: none; color: #64748b; font-size: 16px; padding-bottom: 2px;} QToolButton:hover { color: #f8fafc; }");
    }
}

void LoginWindow::validateEmail(const QString& text) {
    clearError();
    // Reset to normal style
    emailField->setStyleSheet(normalInputStyle);
}

void LoginWindow::checkPasswordStrength(const QString& text) {
    clearError();
    
    int length = text.length();
    int strength = 0;
    
    if (length > 0) strength += 25;
    if (length >= 8) strength += 25;
    if (text.contains(QRegularExpression("[A-Z]"))) strength += 25;
    if (text.contains(QRegularExpression("[0-9|\\W]"))) strength += 25;

    pwdStrengthBar->setValue(strength);
    
    // Colorize based on strength
    QString chunkColor = "#ef4444"; // Red
    if (strength >= 50) chunkColor = "#f59e0b"; // Orange
    if (strength >= 75) chunkColor = "#22c55e"; // Green

    pwdStrengthBar->setStyleSheet(QString(R"(
        QProgressBar { background-color: transparent; border: none; }
        QProgressBar::chunk { background-color: %1; border-radius: 2px; }
    )").arg(chunkColor));
}

void LoginWindow::showError(const QString& message) {
    errorLabel->setText("⚠️ " + message);
    errorLabel->show();
    
    // Input shake animation could go here for extra polish
    emailField->setStyleSheet(errorInputStyle);
}

void LoginWindow::clearError() {
    errorLabel->hide();
}

void LoginWindow::handleLogin() {
    if (emailField->text().isEmpty()) {
        showError("Email Address is required");
        return;
    }
    
    // Basic email validation regex - DISABLED FOR TESTING
    // static QRegularExpression emailRegex("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
    // if (!emailRegex.match(emailField->text()).hasMatch()) {
    //     showError("Format must be: name@kavaro.ai");
    //     return;
    // }
    
    if (passwordField->text().isEmpty()) {
        showError("Password is required for authentication");
        // Mark password container red
        QWidget* pContainer = this->findChild<QWidget*>("pwdContainer");
        if(pContainer) {
            pContainer->setProperty("error", true);
            pContainer->style()->unpolish(pContainer);
            pContainer->style()->polish(pContainer);
        }
        return;
    }
    
    // Enter Loading State
    clearError();
    loginBtn->setEnabled(false);
    loginBtn->setText("Authenticating System...");
    setCursor(Qt::WaitCursor);
    
    // Simulate network delay
    loginTimer->start(1200); 
}

void LoginWindow::finishLogin() {
    // Reset state and emit success
    setCursor(Qt::ArrowCursor);
    loginBtn->setEnabled(true);
    loginBtn->setText("Access Dashboard");
    
    emit loginSuccessful();
}
