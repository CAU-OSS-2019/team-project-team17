#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_OK_clicked()
{
    char buf[1024] = "13.209.7.127";
    signupSock = new SignupSocketClient("signup socket", buf, 9200);
    nickname = ui->lineEdit_lol_nickname->text().toUtf8();
    id = ui->lineEdit_id->text().toUtf8();
    pwd = ui->lineEdit_password->text().toUtf8();

    strncpy(signuInfo.nickname, nickname.toUtf8().constData(), sizeof(signuInfo.nickname));
    strncpy(signuInfo.id, id.toLocal8Bit().constData(), sizeof(signuInfo.id));
    strncpy(signuInfo.pwd, pwd.toLocal8Bit().constData(), sizeof(signuInfo.pwd));


    QMessageBox Msgbox;

    if (nickname.isEmpty() || id.isEmpty() || pwd.isEmpty()) {
        Msgbox.setText("Please write without blank");
        Msgbox.exec();
    } else {
        signupSock->sendData(signuInfo);
        if (signupSock->send_success == -1) {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
        } else {
            signupSuccess = signupSock->receiveData();
            if (signupSuccess) {
                Msgbox.setText("Sign up Complete");
                Msgbox.exec();
                delete signupSock;
                close();
            } else {
                if (signupSock->receive_success == -1) {
                    Msgbox.setText("Sever Error");
                    Msgbox.exec();
                } else {
                Msgbox.setText("Sign up Failed");
                Msgbox.exec();
                }
            }
        }
    }
}
