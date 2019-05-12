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
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username ==  "test" && password == "test") {
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
    }
}
void MainWindow::on_pushButton_Signup_clicked()
{
    //hide();
    signUp = new SignUp(this);
    signUp->show();

}
