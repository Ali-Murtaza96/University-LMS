#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFont>
#include "LoginDialog.h"
#include "AdminWindow.h"
#include "InstructorWindow.h"
#include "StudentWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAdminClicked();
    void onInstructorClicked();
    void onStudentClicked();

private:
    QPushButton *adminButton;
    QPushButton *instructorButton;
    QPushButton *studentButton;
};

#endif
