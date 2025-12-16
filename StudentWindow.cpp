#include "StudentWindow.h"
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFont>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

StudentWindow::StudentWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Student Portal - Bahria University");
    resize(900, 650); // Consistent size with Main Window

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 1. Main Layout (Centers the panel)
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    // 2. Dashboard Panel (The dark transparent box)
    QFrame *dashboardPanel = new QFrame(centralWidget);
    dashboardPanel->setObjectName("Card");
    dashboardPanel->setFixedSize(450, 550);

    // 3. Apply Stylesheet
    centralWidget->setObjectName("bgWidget");
    centralWidget->setStyleSheet(
        "QWidget#bgWidget {"
        "    border-image: url(campus_bg.jpg) 0 0 0 0 stretch stretch;"
        "}"
        "QFrame#Card {"
        "    background-color: rgba(0, 0, 0, 0.75);" /* Dark transparent background */
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
        "    color: #4da6ff;" /* Light Blue Title */
        "    margin-bottom: 15px;"
        "}"
        /* TRANSPARENT BUTTON STYLING */
        "QPushButton {"
        "    background-color: transparent;"
        "    border: 1px solid rgba(255, 255, 255, 0.6);"
        "    color: white;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover { "
        "    background-color: rgba(255, 255, 255, 0.1); "
        "    border: 1px solid white;"
        "}"
        /* Specific Style for Logout (Red Outline) */
        "QPushButton#LogoutBtn {"
        "    border: 1px solid #ff4d4d;"
        "    color: #ff4d4d;"
        "}"
        "QPushButton#LogoutBtn:hover { "
        "    background-color: rgba(255, 77, 77, 0.1); "
        "    border: 1px solid #ff1a1a;"
        "}"
        );

    // 4. Layout inside the Dashboard Panel
    QVBoxLayout *panelLayout = new QVBoxLayout(dashboardPanel);
    panelLayout->setSpacing(10);
    panelLayout->setContentsMargins(40, 40, 40, 40);

    // -- Header --
    QLabel *titleLabel = new QLabel("Student Dashboard", dashboardPanel);
    titleLabel->setObjectName("Header");
    titleLabel->setAlignment(Qt::AlignCenter);
    panelLayout->addWidget(titleLabel);

    // -- Buttons --

    QPushButton *attendanceBtn = new QPushButton("View Attendance", dashboardPanel);
    attendanceBtn->setCursor(Qt::PointingHandCursor);
    connect(attendanceBtn, SIGNAL(clicked()), this, SLOT(onViewAttendance()));
    panelLayout->addWidget(attendanceBtn);

    QPushButton *seatingBtn = new QPushButton("View Seating Plan", dashboardPanel);
    seatingBtn->setCursor(Qt::PointingHandCursor);
    connect(seatingBtn, SIGNAL(clicked()), this, SLOT(onViewSeatingPlan()));
    panelLayout->addWidget(seatingBtn);

    QPushButton *resultsBtn = new QPushButton("View Results", dashboardPanel);
    resultsBtn->setCursor(Qt::PointingHandCursor);
    connect(resultsBtn, SIGNAL(clicked()), this, SLOT(onViewResults()));
    panelLayout->addWidget(resultsBtn);

    QPushButton *feeBtn = new QPushButton("View Fee Challan", dashboardPanel);
    feeBtn->setCursor(Qt::PointingHandCursor);
    connect(feeBtn, SIGNAL(clicked()), this, SLOT(onViewFeeChallan()));
    panelLayout->addWidget(feeBtn);

    QPushButton *assignmentsBtn = new QPushButton("View Assignments", dashboardPanel);
    assignmentsBtn->setCursor(Qt::PointingHandCursor);
    connect(assignmentsBtn, SIGNAL(clicked()), this, SLOT(onViewAssignments()));
    panelLayout->addWidget(assignmentsBtn);

    QPushButton *dashboardBtn = new QPushButton("Dashboard Notifications", dashboardPanel);
    dashboardBtn->setCursor(Qt::PointingHandCursor);
    connect(dashboardBtn, SIGNAL(clicked()), this, SLOT(onViewDashboard()));
    panelLayout->addWidget(dashboardBtn);

    panelLayout->addStretch();

    // -- Logout Button --
    QPushButton *logoutBtn = new QPushButton("Logout", dashboardPanel);
    logoutBtn->setObjectName("LogoutBtn"); // Uses the Red styling
    logoutBtn->setCursor(Qt::PointingHandCursor);
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(onLogout()));
    panelLayout->addWidget(logoutBtn);

    // Add panel to main layout
    mainLayout->addWidget(dashboardPanel);
}

// ---------------------------------------------------------
// Helper Functions
// ---------------------------------------------------------

void StudentWindow::onViewAttendance() { showFileContent("Attendance Records", "Attendance.txt"); }
void StudentWindow::onViewSeatingPlan() { showFileContent("Exam Seating Plan", "SeatingPlan.txt"); }
void StudentWindow::onViewResults() { showFileContent("Results", "Results.txt"); }
void StudentWindow::onViewFeeChallan() { showFileContent("Fee Challan", "FeeChallan.txt"); }
void StudentWindow::onViewAssignments() { showFileContent("Assignments", "Assignments.txt"); }
void StudentWindow::onViewDashboard() { showFileContent("Dashboard Notifications", "Notifications.txt"); }

void StudentWindow::onLogout() {
    this->close();
}

QString StudentWindow::readFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "File not found or empty.";
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    if (content.isEmpty()) {
        return "No data available.";
    }

    return content;
}

void StudentWindow::showFileContent(const QString &title, const QString &filename) {
    QDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.resize(600, 500);

    // Dark Mode Styling for the Popup Window
    dialog.setStyleSheet(
        "QDialog { background-color: #2b2b2b; }"
        "QTextEdit { "
        "   background-color: #1e1e1e; "
        "   color: #e0e0e0; "
        "   border: 1px solid #555; "
        "   border-radius: 5px;"
        "   padding: 10px; "
        "   font-size: 14px; "
        "}"
        /* Close Button inside Dialog */
        "QPushButton { "
        "   background-color: #0078d7; "
        "   color: white; "
        "   border: none; "
        "   border-radius: 5px; "
        "   padding: 8px 20px; "
        "}"
        "QPushButton:hover { background-color: #005a9e; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setText(readFile(filename));
    layout->addWidget(textEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, &dialog);
    connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(accept()));
    layout->addWidget(buttonBox);

    dialog.exec();
}
