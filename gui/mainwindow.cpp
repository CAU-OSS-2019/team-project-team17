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

    strncpy(loginInfo.id, ID.toLocal8Bit().constData(), sizeof(loginInfo.id));
    strncpy(loginInfo.pwd, PW.toLocal8Bit().constData(), sizeof(loginInfo.id));

    QMessageBox Msgbox;

    if (ID.isEmpty() || PW.isEmpty()) {
        Msgbox.setText("Write ID & PASSWORD");
        Msgbox.exec();
    } else {
        char buf[1024] = "13.125.138.196";
        loginSock = new LoginSocketClient("login socket", buf, 9100);
        loginSock->sendData(loginInfo);
        if (loginSock->send_success == -1) {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
            delete loginSock;
        } else {
            userData = loginSock->receiveData();
            cout << "userdata: " << userData.rank << " " << userData.nickname << " " << userData.loginSuccess << " " << sizeof(login_data) << endl;

            if(loginSock->receive_success == -1) {
                delete loginSock;
                Msgbox.setText("Sever Error");
                Msgbox.exec();
            } else {
                if(userData.loginSuccess) {
                    delete loginSock;

                    char buf[1024] = "165.194.17.238";
                    loginSock = new LoginSocketClient("login socket", buf, 9300);
                    loginSock->recvbuf(buf);
                    if (strcmp(buf, "you are connected to server") == 0){
                        cout << buf << endl;
                        ZeroMemory(buf, 1024);
                        strcpy(buf, userData.nickname);
                        loginSock->sendbuf(buf);
                        cout << buf << endl;
                        ZeroMemory(buf, 1024);
                        loginSock->recvbuf(buf);
                        cout << buf << endl;
                        if (strcmp(buf, "SUCCESS") == 0) {
                            ZeroMemory(buf, 1024);
                            strcpy(buf, "quit");
                            cout << buf << endl;
                            loginSock->sendbuf(buf);

                            hide();

                            QSplashScreen *splash =new QSplashScreen;
                            QPixmap qpixmap =(QPixmap(":/img/img/lol_background.jpg"));

                            splash->setPixmap(qpixmap);
                            splash->show();

                            secDialog = new SecDialog(this);
                            secDialog->setData(userData);
                            QTimer::singleShot(2500,splash,SLOT(close));
                            QTimer::singleShot(1500,secDialog,SLOT(show()));
                            splash->finish(secDialog);
                        }
                    }
                } else {
                    delete loginSock;
                    Msgbox.setText("UserID and password is not correct");
                    Msgbox.exec();
                }
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

