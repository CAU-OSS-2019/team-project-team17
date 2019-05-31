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

    QMessageBox Msgbox;

    if (ID.isEmpty() || PW.isEmpty())
    {
        Msgbox.setText("Write ID & PASSWORD");
        Msgbox.exec();
    }
    else
    {
        char buff[1024] = "13.209.15.157";
        loginSock = new LoginSocketClient("login socket", buff, 9100);

        loginSock->sendData(loginInfo);
        if (loginSock->send_success == -1)
        {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
        }
        else
        {
            loginSuccess = loginSock->receiveData();

            if(loginSock->receive_success == -1) {
                delete loginSock;
                Msgbox.setText("Sever Error");
                Msgbox.exec();
            }
            else
            {
                if(loginSuccess)
                {
                    delete loginSock;
/*
                    loginSock = new LoginSocketClient("crwaling socket", "127.0.0.1", 8080);

                    buf = "nickname";
                    loginSock->sendbuf(buf);
                    loginSock->recvbuf(buf);

                    if (strcmp(("SUCESS"), buf)) {
                        buf = "/quit";
                        loginSock->sendbuf(buf);

                        delete loginSock;

                        QMessageBox::information(this, "Login", "Username and password is correct");
                        hide();
*/
                        QSplashScreen *splash =new QSplashScreen;
                        QPixmap qpixmap =(QPixmap(":/img/img/lol_background.jpg"));

                        splash->setPixmap(qpixmap);
                        splash->show();

                        secDialog = new SecDialog(this);
                        QTimer::singleShot(2500,splash,SLOT(close));
                        QTimer::singleShot(1500,secDialog,SLOT(show()));
                        splash->finish(secDialog);
//                    }

                }
                else
                {
                    Msgbox.setText("UserID and password is not correct");
                    Msgbox.exec();
                }
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
        }
    }
}

void MainWindow::on_pushButton_Signup_clicked()
{
    //hide();
    signUp = new SignUp(this);
    signUp->show();
}

