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
    setWindowTitle("Kavaro | Operational Access");
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
    // LEFT SIDE: BRANDING / IMAGE PANEL (DARK)
    // =====================================
    auto* leftFrame = new QFrame;
    leftFrame->setFixedWidth(500); 
    leftFrame->setStyleSheet(R"(
        QFrame {
            background-color: #0b0f1a;
            border: none;
        }
    )");
    
    auto* leftLayout = new QVBoxLayout(leftFrame);
    leftLayout->setContentsMargins(50, 60, 50, 60);
    
    auto* logoLabel = new QLabel("◆ KAVARO ADDITIVE");
    logoLabel->setStyleSheet("color: #3b82f6; font-size: 14px; font-weight: 900; letter-spacing: 4px; background: transparent;");
    
    auto* bigImageLabel = new QLabel;
    bigImageLabel->setStyleSheet("background: transparent;");
    QPixmap logoPixmap("D:/Kavaro_decktop/kavaro.png");
    if (!logoPixmap.isNull()) {
        bigImageLabel->setPixmap(logoPixmap.scaled(380, 380, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        bigImageLabel->setText("[ KAVARO 3D ]");
        bigImageLabel->setStyleSheet("color: #1e293b; font-size: 24px; font-weight: 900; background: transparent;");
    }
    bigImageLabel->setAlignment(Qt::AlignCenter);
    
    auto* brandingContainer = new QVBoxLayout;
    auto* brandingTitle = new QLabel("Precision in Every Layer.");
    brandingTitle->setStyleSheet("color: white; font-size: 28px; font-weight: 800; background: transparent;");
    
    auto* brandingDesc = new QLabel("System control for Kavaro Additive Manufacturing. Manage your fleet and high-precision prints in real-time.");
    brandingDesc->setStyleSheet("color: #64748b; font-size: 14px; font-weight: 400; line-height: 1.5; background: transparent;");
    brandingDesc->setWordWrap(true);
    
    brandingContainer->addWidget(brandingTitle);
    brandingContainer->addWidget(brandingDesc);
    
    leftLayout->addWidget(logoLabel);
    leftLayout->addStretch();
    leftLayout->addWidget(bigImageLabel);
    leftLayout->addStretch();
    leftLayout->addLayout(brandingContainer);
    
    mainLayout->addWidget(leftFrame);

    // =====================================
    // RIGHT SIDE: LOGIN FORM
    // =====================================
    auto* rightWidget = new QWidget;
    auto* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(80, 0, 80, 0); 
    rightLayout->setSpacing(35);
    
    auto* formContainer = new QWidget;
    auto* formLayout = new QVBoxLayout(formContainer);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(15); 
    
    // Form Header
    auto* titleLabel = new QLabel("Operator Login");
    titleLabel->setStyleSheet("color: #ffffff; font-size: 36px; font-weight: 900; letter-spacing: -1px;");
    
    auto* subtitleLabel = new QLabel("Enter keys to access the 3D manufacturing dashboard");
    subtitleLabel->setStyleSheet("color: #64748b; font-size: 14px; font-weight: 400; margin-bottom: 20px;");
    
    formLayout->addWidget(titleLabel);
    formLayout->addWidget(subtitleLabel);
    formLayout->addSpacing(10);
    
    // --- EMAIL ---
    auto* emailLabel = new QLabel("SYSTEM ID");
    emailLabel->setStyleSheet("color: #64748b; font-size: 11px; font-weight: 800; letter-spacing: 1.5px;");
    formLayout->addWidget(emailLabel);
    
    emailField = new QLineEdit;
    emailField->setPlaceholderText("operator@kavaro.ai");
    emailField->setFixedHeight(55);
    emailField->setStyleSheet(normalInputStyle);
    formLayout->addWidget(emailField);
    
    connect(emailField, &QLineEdit::textChanged, this, &LoginWindow::validateEmail);

    // --- PASSWORD ---
    auto* passLabel = new QLabel("ACCESS KEY");
    passLabel->setStyleSheet("color: #64748b; font-size: 11px; font-weight: 800; letter-spacing: 1.5px;");
    formLayout->addWidget(passLabel);
    
    auto* pwdContainer = new QWidget;
    pwdContainer->setFixedHeight(55);
    pwdContainer->setObjectName("pwdContainer");
    pwdContainer->setStyleSheet(R"(
        QWidget#pwdContainer { background-color: #1e293b; border: 1px solid #334155; border-radius: 12px; }
        QWidget#pwdContainer[focus="true"] { border: 1px solid #3b82f6; background-color: #0f172a; }
    )");
    
    auto* pwdLayout = new QHBoxLayout(pwdContainer);
    pwdLayout->setContentsMargins(20, 0, 10, 0);
    
    passwordField = new QLineEdit;
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setPlaceholderText("••••••••••••");
    passwordField->setStyleSheet("QLineEdit { background: transparent; border: none; color: #f8fafc; font-size: 16px; }");
    
    connect(passwordField, &QLineEdit::textChanged, this, &LoginWindow::checkPasswordStrength);
    
    togglePwdBtn = new QToolButton;
    togglePwdBtn->setText("👁");
    togglePwdBtn->setCursor(Qt::PointingHandCursor);
    togglePwdBtn->setStyleSheet("QToolButton { background: transparent; border: none; color: #64748b; font-size: 18px; }");
    connect(togglePwdBtn, &QToolButton::clicked, this, &LoginWindow::togglePasswordVisibility);
    
    pwdLayout->addWidget(passwordField);
    pwdLayout->addWidget(togglePwdBtn);
    formLayout->addWidget(pwdContainer);
    
    pwdStrengthBar = new QProgressBar;
    pwdStrengthBar->setFixedHeight(4);
    pwdStrengthBar->setTextVisible(false);
    pwdStrengthBar->setStyleSheet("QProgressBar { background: transparent; border: none; } QProgressBar::chunk { border-radius: 2px; }");
    formLayout->addWidget(pwdStrengthBar);
    
    auto* extrasLayout = new QHBoxLayout;
    rememberMeCb = new QCheckBox("Stay Synced");
    rememberMeCb->setStyleSheet("QCheckBox { color: #94a3b8; font-size: 13px; } QCheckBox::indicator { width: 18px; height: 18px; border-radius: 4px; border: 1px solid #334155; }");
    forgotPwdLabel = new QLabel("<a href='#' style='color: #3b82f6; text-decoration: none; font-size: 13px; font-weight: bold;'>Restore Access?</a>");
    extrasLayout->addWidget(rememberMeCb);
    extrasLayout->addStretch();
    extrasLayout->addWidget(forgotPwdLabel);
    formLayout->addLayout(extrasLayout);

    loginBtn = new QPushButton("Initialize Session");
    loginBtn->setFixedHeight(60);
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setStyleSheet(R"(
        QPushButton { 
            background: #3b82f6;
            color: white; border: none; border-radius: 12px; font-size: 16px; font-weight: 800;
        }
        QPushButton:hover { background: #2563eb; }
    )");
    formLayout->addSpacing(10);
    formLayout->addWidget(loginBtn);
    
    errorLabel = new QLabel("");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setStyleSheet("color: #ef4444; font-size: 13px; font-weight: bold; background: rgba(239, 68, 68, 0.1); border-radius: 8px; padding: 12px;");
    errorLabel->hide();
    formLayout->addWidget(errorLabel);
    
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
        togglePwdBtn->setText("🙈"); 
        togglePwdBtn->setStyleSheet("QToolButton { background: transparent; border: none; color: #3b82f6; font-size: 18px; }");
    } else {
        passwordField->setEchoMode(QLineEdit::Password);
        togglePwdBtn->setText("👁");
        togglePwdBtn->setStyleSheet("QToolButton { background: transparent; border: none; color: #64748b; font-size: 18px; }");
    }
}

void LoginWindow::validateEmail(const QString& text) {
    clearError();
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
    QString chunkColor = "#ef4444"; 
    if (strength >= 50) chunkColor = "#f59e0b"; 
    if (strength >= 75) chunkColor = "#22c55e"; 
    pwdStrengthBar->setStyleSheet(QString(R"(
        QProgressBar { background-color: transparent; border: none; }
        QProgressBar::chunk { background-color: %1; border-radius: 2px; }
    )").arg(chunkColor));
}

void LoginWindow::showError(const QString& message) {
    errorLabel->setText("⚠️ " + message);
    errorLabel->show();
    emailField->setStyleSheet(errorInputStyle);
}

void LoginWindow::clearError() {
    errorLabel->hide();
}

void LoginWindow::handleLogin() {
    if (emailField->text().isEmpty()) {
        showError("ID required");
        return;
    }
    if (passwordField->text().isEmpty()) {
        showError("Access Key required");
        return;
    }
    clearError();
    loginBtn->setEnabled(false);
    loginBtn->setText("Initializing...");
    setCursor(Qt::WaitCursor);
    loginTimer->start(1200); 
}

void LoginWindow::finishLogin() {
    setCursor(Qt::ArrowCursor);
    loginBtn->setEnabled(true);
    loginBtn->setText("Initialize Session");
    emit loginSuccessful();
}
