#include "InstructorWindow.h"
#include "Date.h"
#include "Assignment.h"
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

// Common Stylesheet for Popup Dialogs to match Dark Theme
const QString DIALOG_STYLE =
    "QDialog { background-color: #2b2b2b; }"
    "QLabel { color: white; font-size: 14px; }"
    "QLineEdit, QSpinBox, QDateEdit { "
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

InstructorWindow::InstructorWindow(QWidget *parent)
    : QMainWindow(parent), currentCourse(nullptr) {
    setWindowTitle("Instructor Panel - Bahria University");
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
    QLabel *titleLabel = new QLabel("Instructor Dashboard", dashboardPanel);
    titleLabel->setObjectName("Header");
    titleLabel->setAlignment(Qt::AlignCenter);
    panelLayout->addWidget(titleLabel);

    // Buttons
    QPushButton *createCourseBtn = new QPushButton("Select Course", dashboardPanel);
    createCourseBtn->setCursor(Qt::PointingHandCursor);
    connect(createCourseBtn, &QPushButton::clicked, this, &InstructorWindow::onCreateCourse);
    panelLayout->addWidget(createCourseBtn);

    QPushButton *assignmentBtn = new QPushButton("Upload Assignment", dashboardPanel);
    assignmentBtn->setCursor(Qt::PointingHandCursor);
    connect(assignmentBtn, &QPushButton::clicked, this, &InstructorWindow::onUploadAssignment);
    panelLayout->addWidget(assignmentBtn);

    QPushButton *attendanceBtn = new QPushButton("Mark Attendance", dashboardPanel);
    attendanceBtn->setCursor(Qt::PointingHandCursor);
    connect(attendanceBtn, &QPushButton::clicked, this, &InstructorWindow::onMarkAttendance);
    panelLayout->addWidget(attendanceBtn);

    QPushButton *viewCourseBtn = new QPushButton("View Course Information", dashboardPanel);
    viewCourseBtn->setCursor(Qt::PointingHandCursor);
    connect(viewCourseBtn, &QPushButton::clicked, this, &InstructorWindow::onViewCourseInfo);
    panelLayout->addWidget(viewCourseBtn);

    panelLayout->addStretch();

    // Logout
    QPushButton *logoutBtn = new QPushButton("Logout", dashboardPanel);
    logoutBtn->setObjectName("LogoutBtn");
    logoutBtn->setCursor(Qt::PointingHandCursor);
    connect(logoutBtn, &QPushButton::clicked, this, &InstructorWindow::onLogout);
    panelLayout->addWidget(logoutBtn);

    mainLayout->addWidget(dashboardPanel);
}

InstructorWindow::~InstructorWindow() {
    if (currentCourse) {
        delete currentCourse;
    }
}

// ---------------------------------------------------------
// Logic Functions (With Styled Dialogs)
// ---------------------------------------------------------

void InstructorWindow::onCreateCourse() {
    QDialog dialog(this);
    dialog.setWindowTitle("Create New Course");
    dialog.setFixedSize(400, 300);
    dialog.setStyleSheet(DIALOG_STYLE); // Apply Dark Theme

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    QLineEdit *codeEdit = new QLineEdit(&dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    QLineEdit *sectionEdit = new QLineEdit(&dialog);
    QSpinBox *creditsSpin = new QSpinBox(&dialog);
    creditsSpin->setRange(1, 6);
    creditsSpin->setValue(3);

    formLayout->addRow("Course Code:", codeEdit);
    formLayout->addRow("Course Name:", nameEdit);
    formLayout->addRow("Section:", sectionEdit);
    formLayout->addRow("Credits:", creditsSpin);

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        if (currentCourse) {
            delete currentCourse;
        }

        currentCourse = new Course(
            codeEdit->text().toStdString(),
            nameEdit->text().toStdString(),
            sectionEdit->text().toStdString(),
            creditsSpin->value()
            );

        QString content = QString("Code: %1 | Section: %2 | Name: %3")
                              .arg(codeEdit->text())
                              .arg(sectionEdit->text())
                              .arg(nameEdit->text());

        appendToFile("Courses.txt", content);
        QMessageBox::information(this, "Success", "Course selected successfully!");
    }
}

void InstructorWindow::onUploadAssignment() {
    if (!currentCourse) {
        QMessageBox::warning(this, "Error", "Please select a course first!");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Upload Assignment");
    dialog.setFixedSize(400, 250);
    dialog.setStyleSheet(DIALOG_STYLE); // Apply Dark Theme

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    QLineEdit *titleEdit = new QLineEdit(&dialog);
    QSpinBox *marksSpin = new QSpinBox(&dialog);
    marksSpin->setRange(0, 1000);
    marksSpin->setValue(100);
    QDateEdit *dueDateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dueDateEdit->setCalendarPopup(true);

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Total Marks:", marksSpin);
    formLayout->addRow("Due Date:", dueDateEdit);

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        QDate qDate = dueDateEdit->date();
        Date dueDate(qDate.day(), qDate.month(), qDate.year());

        Assignment *asg = new Assignment(
            titleEdit->text().toStdString(),
            marksSpin->value(),
            dueDate
            );

        currentCourse->addAssignment(asg);

        QString content = QString("Course: %1 | Title: %2 | Marks: %3 | Due: %4")
                              .arg(QString::fromStdString(currentCourse->courseCode))
                              .arg(titleEdit->text())
                              .arg(marksSpin->value())
                              .arg(dueDateEdit->date().toString("dd/MM/yyyy"));

        appendToFile("Assignments.txt", content);
        QMessageBox::information(this, "Success", "Assignment uploaded successfully!");
    }
}

void InstructorWindow::onMarkAttendance() {
    if (!currentCourse) {
        QMessageBox::warning(this, "Error", "Please create a course first!");
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Mark Attendance");
    dialog.setFixedSize(400, 250);
    dialog.setStyleSheet(DIALOG_STYLE); // Apply Dark Theme

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    QLineEdit *studentIdEdit = new QLineEdit(&dialog);
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dateEdit->setCalendarPopup(true);
    QLineEdit *statusEdit = new QLineEdit("P", &dialog);

    formLayout->addRow("Student ID:", studentIdEdit);
    formLayout->addRow("Date:", dateEdit);
    formLayout->addRow("Status (P/A):", statusEdit);

    layout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        QDate qDate = dateEdit->date();
        Date attDate(qDate.day(), qDate.month(), qDate.year());

        currentCourse->markAttendance(
            studentIdEdit->text().toStdString(),
            attDate,
            statusEdit->text().toStdString()
            );

        QString content = QString("Course: %1 | Student: %2 | Date: %3 | Status: %4")
                              .arg(QString::fromStdString(currentCourse->courseCode))
                              .arg(studentIdEdit->text())
                              .arg(dateEdit->date().toString("dd/MM/yyyy"))
                              .arg(statusEdit->text());

        appendToFile("Attendance.txt", content);
        QMessageBox::information(this, "Success", "Attendance marked successfully!");
    }
}

void InstructorWindow::onViewCourseInfo() {
    if (!currentCourse) {
        QMessageBox::warning(this, "Error", "No course created yet!");
        return;
    }

    QString info = QString("Course Information:\n\n"
                           "Code: %1\n"
                           "Name: %2\n"
                           "Section: %3\n"
                           "Credits: %4")
                       .arg(QString::fromStdString(currentCourse->courseCode))
                       .arg(QString::fromStdString(currentCourse->courseName))
                       .arg(QString::fromStdString(currentCourse->section))
                       .arg(currentCourse->credits);

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Course Information");
    msgBox.setText(info);
    msgBox.setStyleSheet(DIALOG_STYLE); // Style the message box too
    msgBox.exec();
}

void InstructorWindow::onLogout() {
    this->close();
}

void InstructorWindow::appendToFile(const QString &filename, const QString &content) {
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << content << "\n";
        file.close();
    }
}
