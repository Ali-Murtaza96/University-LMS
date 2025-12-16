#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QMessageBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>

class AdminWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

private slots:
    void onGenerateFeeChallan();
    void onUploadSeatingPlan();
    void onUploadResults();
    void onUpdateDashboard();
    void onLogout();

private:
    void appendToFile(const QString &filename, const QString &content);
};

#endif
