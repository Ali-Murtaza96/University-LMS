#include "AdminWindow.h"
#include <QFile>
#include <QTextStream>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QFont>
#include <QMessageBox>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QTextEdit>

// Common Stylesheet for Popup Dialogs
const QString DIALOG_STYLE =
    "QDialog { background-color: #2b2b2b; }"
    "QLabel { color: white; font-size: 14px; }"
    "QLineEdit, QSpinBox, QDateEdit, QTextEdit { "
    "    background-color: #1e1e1e; "
    "    color: white; "
    "    border: 1px solid #555; "
    "    border-radius: 4px; "
    "    padding: 6px; "
    "}"
    "QPushButton { "
    "    background-color: #0078d7; "
    "    color: white; "
    "    border-radius: 4px; "
    "    padding: 8px 15px; "
    "    font-weight: bold; "
    "}"
    "QPushButton:hover { background-color: #005a9e; }";

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Admin Panel - Bahria University");
    resize(900, 650);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 1. Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 2. Dashboard Panel
    QFrame *dashboardPanel = new QFrame(centralWidget);
    dashboardPanel->setObjectName("Card");
    dashboardPanel->setFixedSize(450, 550);

    // 3. Apply Main Stylesheet
    centralWidget->setObjectName("bgWidget");
    centralWidget->setStyleSheet(
        "QWidget#bgWidget {"
        "    border-image: url(campus_bg.jpg) 0 0 0 0 stretch stretch;"
        "}"
        "QFrame#Card {"
        "    background-color: rgba(0, 0, 0, 0.75);" /* Dark transparent bg */
        "    border-radius: 20px;"
        "    border: 1px solid rgba(255, 255, 255, 0.1);"
        "}"
        "QLabel {"
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    background: transparent;"
        "    border: none;"
        "}"
        "QLabel#Header {"
        "    font-size: 26px;"
        "    color: #4da6ff;"
        "    margin-bottom: 15px;"
        "}"
        /* Transparent Glass Buttons */
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 1px solid rgba(255, 255, 255, 0.6);"
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 12px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover { "
        "    background-color: rgba(255, 255, 255, 0.1); "
        "    border: 1px solid white;"
        "}"
        /* Logout Button (Red Outline) */
        "QPushButton#LogoutBtn {"
        "    border: 1px solid #ff4d4d;"
        "    color: #ff4d4d;"
        "}"
        "QPushButton#LogoutBtn:hover { "
        "    background-color: rgba(255, 77, 77, 0.1); "
        "    border: 1px solid #ff1a1a;"
        "}"
        );

    // 4. Panel Layout
    QVBoxLayout *panelLayout = new QVBoxLayout(dashboardPanel);
    panelLayout->setSpacing(15);
    panelLayout->setContentsMargins(40, 40, 40, 40);

    // Header
    QLabel *titleLabel = new QLabel("Admin Dashboard", dashboardPanel);
    titleLabel->setObjectName("Header");
    titleLabel->setAlignment(Qt::AlignCenter);
    panelLayout->addWidget(titleLabel);

    // Buttons
    QPushButton *feeBtn = new QPushButton("Generate Fee Challan", dashboardPanel);
    feeBtn->setCursor(Qt::PointingHandCursor);
    connect(feeBtn, &QPushButton::clicked, this, &AdminWindow::onGenerateFeeChallan);
    panelLayout->addWidget(feeBtn);

    QPushButton *seatingBtn = new QPushButton("Upload Exam Seating Plan", dashboardPanel);
    seatingBtn->setCursor(Qt::PointingHandCursor);
    connect(seatingBtn, &QPushButton::clicked, this, &AdminWindow::onUploadSeatingPlan);
    panelLayout->addWidget(seatingBtn);

    QPushButton *resultsBtn = new QPushButton("Upload Results", dashboardPanel);
    resultsBtn->setCursor(Qt::PointingHandCursor);
    connect(resultsBtn, &QPushButton::clicked, this, &AdminWindow::onUploadResults);
    panelLayout->addWidget(resultsBtn);

    QPushButton *dashboardBtn = new QPushButton("Update Dashboard", dashboardPanel);
    dashboardBtn->setCursor(Qt::PointingHandCursor);
    connect(dashboardBtn, &QPushButton::clicked, this, &AdminWindow::onUpdateDashboard);
    panelLayout->addWidget(dashboardBtn);

    panelLayout->addStretch();

    // Logout
    QPushButton *logoutBtn = new QPushButton("Logout", dashboardPanel);
    logoutBtn->setObjectName("LogoutBtn");
    logoutBtn->setCursor(Qt::PointingHandCursor);
    connect(logoutBtn, &QPushButton::clicked, this, &AdminWindow::onLogout);
    panelLayout->addWidget(logoutBtn);

    mainLayout->addWidget(dashboardPanel);
}

// ---------------------------------------------------------
// Logic Functions (With Styled Dialogs)
// ---------------------------------------------------------

void AdminWindow::onGenerateFeeChallan() {
    QDialog dialog(this);
    dialog.setWindowTitle("Generate Fee Challan");
    dialog.setFixedSize(400, 250);
    dialog.setStyleSheet(DIALOG_STYLE);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    QLineEdit *studentIdEdit = new QLineEdit(&dialog);
    QSpinBox *amountSpin = new QSpinBox(&dialog);
    amountSpin->setRange(0, 1000000);
    amountSpin->setValue(50000);
    QDateEdit *dueDateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dueDateEdit->setCalendarPopup(true);

    formLayout->addRow("Student ID:", studentIdEdit);
    formLayout->addRow("Amount:", amountSpin);
    formLayout->addRow("Due Date:", dueDateEdit);

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        QString content = QString("Student: %1 | Amount: %2 | Due: %3 | Status: Unpaid")
        .arg(studentIdEdit->text())
            .arg(amountSpin->value())
            .arg(dueDateEdit->date().toString("dd/MM/yyyy"));

        appendToFile("FeeChallan.txt", content);
        QMessageBox::information(this, "Success", "Fee Challan generated successfully!");
    }
}

void AdminWindow::onUploadSeatingPlan() {
    QDialog dialog(this);
    dialog.setWindowTitle("Upload Seating Plan");
    dialog.setFixedSize(500, 400);
    dialog.setStyleSheet(DIALOG_STYLE);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Enter Seating Plan Details:", &dialog);
    layout->addWidget(label);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    layout->addWidget(textEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        appendToFile("SeatingPlan.txt", textEdit->toPlainText());
        QMessageBox::information(this, "Success", "Seating Plan uploaded successfully!");
    }
}

void AdminWindow::onUploadResults() {
    QDialog dialog(this);
    dialog.setWindowTitle("Upload Results");
    dialog.setFixedSize(500, 400);
    dialog.setStyleSheet(DIALOG_STYLE);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Enter Result Details:", &dialog);
    layout->addWidget(label);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    layout->addWidget(textEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        appendToFile("Results.txt", textEdit->toPlainText());
        QMessageBox::information(this, "Success", "Results uploaded successfully!");
    }
}

void AdminWindow::onUpdateDashboard() {
    QDialog dialog(this);
    dialog.setWindowTitle("Update Dashboard");
    dialog.setFixedSize(400, 200);
    dialog.setStyleSheet(DIALOG_STYLE);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Enter Notification:", &dialog);
    layout->addWidget(label);

    QLineEdit *lineEdit = new QLineEdit(&dialog);
    layout->addWidget(lineEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        QString notification = "[Notification] " + lineEdit->text();
        appendToFile("Notifications.txt", notification);
        QMessageBox::information(this, "Success", "Dashboard updated successfully!");
    }
}

void AdminWindow::onLogout() {
    this->close();
}

void AdminWindow::appendToFile(const QString &filename, const QString &content) {
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << content << "\n";
        file.close();
    }
}
