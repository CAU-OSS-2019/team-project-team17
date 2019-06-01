#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <string>
#include "secdialog.h"
#include "signup.h"
#include "login.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();
    void on_pushButton_Signup_clicked();

private:
    Ui::MainWindow *ui;
    SecDialog *secDialog;
    SignUp *signUp;
    login_info loginInfo;
    login_data userData;
    LoginSocketClient *loginSock;
    char *buf;
    QString ID;
    QString PW;
};

#endif // MAINWINDOW_H
