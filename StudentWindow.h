#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QDialog>
#include <QDialogButtonBox>

class StudentWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);

private slots:
    void onViewAttendance();
    void onViewSeatingPlan();
    void onViewResults();
    void onViewFeeChallan();
    void onViewAssignments();
    void onViewDashboard();
    void onLogout();

private:
    QString readFile(const QString &filename);
    void showFileContent(const QString &title, const QString &filename);
};

#endif
