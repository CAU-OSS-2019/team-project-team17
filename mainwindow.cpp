#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


//    loginSock = new LoginSocketClient("login socket", "13.209.15.157", 8888);
    ui->setupUi(this);
    //QPixmap pix(":/resources/img/login-icon.png");
    //int w = ui->label_pic->width();
    //int h = ui->label_pic->height();
   // ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    ID = ui->lineEdit_username->text().toUtf8();
    PW = ui->lineEdit_password->text().toUtf8();

    loginInfo.id = ID.toLocal8Bit().constData();
    loginInfo.pwd = PW.toLocal8Bit().constData();
/*
    loginSock->sendData(loginInfo);
    loginSuccess = loginSock->receiveData();

    if(loginSuccess) {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();

        QSplashScreen *splash =new QSplashScreen;
        QPixmap qpixmap =(QPixmap(":/img/img/lol_background.jpg"));

        splash->setPixmap(qpixmap);
        splash->show();

        secDialog = new SecDialog(this);
        QTimer::singleShot(2500,splash,SLOT(close));
        QTimer::singleShot(1500,secDialog,SLOT(show()));
        splash->finish(secDialog);
    }
    else {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }*/

    hide();

    QSplashScreen *splash =new QSplashScreen;
    QPixmap qpixmap =(QPixmap(":/img/img/lol_background.jpg"));

    splash->setPixmap(qpixmap);
    splash->show();

    secDialog = new SecDialog(this);
    QTimer::singleShot(2500,splash,SLOT(close));
    QTimer::singleShot(1500,secDialog,SLOT(show()));
    splash->finish(secDialog);
}

void MainWindow::on_pushButton_Signup_clicked()
{
    //hide();
    signUp = new SignUp(this);
    signUp->show();

}
