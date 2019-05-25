#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMovie>
#include "signup_socket.h"

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
    void MainPosition();
    void SubPositon();
    void on_pushButton_OK_clicked();
private:
    Ui::SignUp *ui;
    SignupSocketClient *signupSock;
    signup_info signuInfo;
    bool signupSuccess = false;
    QString id;
    QString pwd;
    QString nickname;
    QString mainPosition;
    QString subPosition;
};

#endif // SIGNUP_H
