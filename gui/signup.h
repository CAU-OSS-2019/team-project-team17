#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include "signup_socket.h"
#include <string>
#include <string.h>
#include <Windows.h>
#include <ShlObj.h>
#include <tchar.h>
#include <fstream>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
private slots:
    void on_pushButton_OK_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::SignUp *ui;
    SignupSocketClient *signupSock;
    signup_info signuInfo;
    bool signupSuccess = false;
    QString id;
    QString pwd;
    QString nickname;
};

#endif // SIGNUP_H
