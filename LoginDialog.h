#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDialogButtonBox>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(const QString &userType, QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
};

#endif
