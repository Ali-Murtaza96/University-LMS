#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>

LoginDialog::LoginDialog(const QString &userType, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle(userType + " Login - Bahria University");
    setFixedSize(900, 650);

    // 1. Setup Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 2. Create Container Frame
    QFrame *loginContainer = new QFrame(this);
    loginContainer->setFixedSize(320, 350); // Slightly smaller height since labels are gone

    // 3. Apply Stylesheet
    setStyleSheet(
        "QDialog {"
        "    border-image: url(campus_bg.jpg) 0 0 0 0 stretch stretch;"
        "}"
        "QFrame {"
        "    background-color: rgba(0, 0, 0, 0.65);"
        "    border-radius: 15px;"
        "}"
        "QLabel#Heading {"
        "    font-size: 26px;"
        "    font-weight: bold;"
        "    color: white;"
        "    margin-bottom: 20px;"
        "    background: transparent;"
        "}"
        "QLineEdit {"
        "    background-color: rgba(255, 255, 255, 0.1);" /* Very subtle background */
        "    border: 1px solid rgba(255, 255, 255, 0.2);" /* Subtle border */
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    font-size: 14px;"
        "    color: white;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #4da6ff;" /* Highlight on click */
        "    background-color: rgba(255, 255, 255, 0.15);"
        "}"
        "QPushButton {"
        "    background-color: #0078d7;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    margin-top: 10px;"
        "}"
        "QPushButton:hover { background-color: #005a9e; }"
        "QPushButton#CancelBtn { background-color: transparent; border: 1px solid rgba(255,255,255,0.5); }"
        "QPushButton#CancelBtn:hover { background-color: rgba(255, 255, 255, 0.1); }"
        );

    // 4. Setup Layout inside the Container
    QVBoxLayout *containerLayout = new QVBoxLayout(loginContainer);
    containerLayout->setSpacing(15);
    containerLayout->setContentsMargins(30, 40, 30, 40);

    // Title (Centered)
    QLabel *titleLabel = new QLabel(userType, loginContainer);
    titleLabel->setObjectName("Heading");
    titleLabel->setAlignment(Qt::AlignCenter);
    containerLayout->addWidget(titleLabel);

    // Username Input (No Label above it)
    usernameEdit = new QLineEdit(loginContainer);
    usernameEdit->setPlaceholderText("Username"); // Text is now inside
    containerLayout->addWidget(usernameEdit);

    // Password Input (No Label above it)
    passwordEdit = new QLineEdit(loginContainer);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Password"); // Text is now inside
    containerLayout->addWidget(passwordEdit);

    // Buttons
    loginButton = new QPushButton("Login", loginContainer);
    cancelButton = new QPushButton("Cancel", loginContainer);
    cancelButton->setObjectName("CancelBtn");

    containerLayout->addWidget(loginButton);
    containerLayout->addWidget(cancelButton);

    // Add stretch to push everything to the center/top slightly
    containerLayout->addStretch();

    mainLayout->addWidget(loginContainer);

    connect(loginButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString LoginDialog::getUsername() const {
    return usernameEdit->text();
}

QString LoginDialog::getPassword() const {
    return passwordEdit->text();
}
