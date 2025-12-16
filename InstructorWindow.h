#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QMessageBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "Course.h"

class InstructorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit InstructorWindow(QWidget *parent = nullptr);
    ~InstructorWindow();

private slots:
    void onCreateCourse();
    void onUploadAssignment();
    void onMarkAttendance();
    void onViewCourseInfo();
    void onLogout();

private:
    Course *currentCourse;
    void appendToFile(const QString &filename, const QString &content);
};

#endif
