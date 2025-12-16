#include "MainWindow.h"
#include "LoginDialog.h"
#include "AdminWindow.h"
#include "InstructorWindow.h"
#include "StudentWindow.h"
#include <QMessageBox>
#include <QFont>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("University LMS");
    setFixedSize(900, 650);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 1. Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 2. Create the Central Card
    QFrame *menuPanel = new QFrame(centralWidget);
    menuPanel->setObjectName("Card");
    menuPanel->setFixedSize(400, 450);

    // 3. Apply Stylesheet
    centralWidget->setObjectName("bgWidget");
    centralWidget->setStyleSheet(
        "QWidget#bgWidget {"
        "    border-image: url(campus_bg.jpg) 0 0 0 0 stretch stretch;"
        "}"
        "QFrame#Card {"
        "    background-color: rgba(0, 0, 0, 0.75);" /* Dark transparent panel */
        "    border-radius: 20px;"
        "    border: 1px solid rgba(255, 255, 255, 0.1);"
        "}"
        "QLabel {"
        "    color: white;"
        "    font-size: 16px;"
        "    background: transparent;"
        "}"
        "QLabel#Title {"
        "    font-size: 28px;"
        "    font-weight: bold;"
        "    color: #4da6ff;"
        "    margin-bottom: 5px;"
        "}"
        /* TRANSPARENT BUTTON STYLING */
        "QPushButton {"
        "    background-color: transparent;" /* No fill color */
        "    border: 1px solid rgba(255, 255, 255, 0.6);" /* White outline */
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(255, 255, 255, 0.1);" /* Slight white tint on hover */
        "    border: 1px solid white;" /* Brighter border on hover */
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(255, 255, 255, 0.2);"
        "}"
        );

    // 4. Layout inside the Panel
    QVBoxLayout *panelLayout = new QVBoxLayout(menuPanel);
    panelLayout->setSpacing(20);
    panelLayout->setContentsMargins(40, 50, 40, 50);

    // -- Title --
    QLabel *titleLabel = new QLabel("UNIVERSITY LMS", menuPanel);
    titleLabel->setObjectName("Title");
    titleLabel->setAlignment(Qt::AlignCenter);
    panelLayout->addWidget(titleLabel);

    QLabel *subtitleLabel = new QLabel("Select User Type", menuPanel);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #ccc; font-size: 14px; margin-bottom: 10px;");
    panelLayout->addWidget(subtitleLabel);

    // -- Buttons --
    adminButton = new QPushButton("Admin Portal", menuPanel);
    adminButton->setCursor(Qt::PointingHandCursor);
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminClicked);
    panelLayout->addWidget(adminButton);

    instructorButton = new QPushButton("Instructor Portal", menuPanel);
    instructorButton->setCursor(Qt::PointingHandCursor);
    connect(instructorButton, &QPushButton::clicked, this, &MainWindow::onInstructorClicked);
    panelLayout->addWidget(instructorButton);

    studentButton = new QPushButton("Student Portal", menuPanel);
    studentButton->setCursor(Qt::PointingHandCursor);
    connect(studentButton, &QPushButton::clicked, this, &MainWindow::onStudentClicked);
    panelLayout->addWidget(studentButton);

    panelLayout->addStretch();

    mainLayout->addWidget(menuPanel);
}

MainWindow::~MainWindow() {}

// ---------------------------------------------------------
// Logic Functions
// ---------------------------------------------------------

void MainWindow::onAdminClicked() {
    LoginDialog dialog("Admin", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        if (username == "Admin@buic.edu" && password == "bahria1") {
            AdminWindow *adminWin = new AdminWindow();
            adminWin->show();
            this->hide();
            connect(adminWin, &AdminWindow::destroyed, this, &MainWindow::show);
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        }
    }
}

void MainWindow::onInstructorClicked() {
    LoginDialog dialog("Instructor", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        if (username == "Prof.Aleem@buic.edu" && password == "bahria2") {
            InstructorWindow *instWin = new InstructorWindow();
            instWin->show();
            this->hide();
            connect(instWin, &InstructorWindow::destroyed, this, &MainWindow::show);
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        }
    }
}

void MainWindow::onStudentClicked() {
    LoginDialog dialog("Student", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        if (username == "Ali@buic.edu" && password == "bahria3") {
            StudentWindow *studWin = new StudentWindow();
            studWin->show();
            this->hide();
            connect(studWin, &StudentWindow::destroyed, this, &MainWindow::show);
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        }
    }
}
