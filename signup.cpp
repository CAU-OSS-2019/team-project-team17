#include "signup.h"
#include "ui_signup.h"

#include <QMessageBox>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
//    signupSock = new SignupSocketClient("signup socket", "13.209.15.157", 8888);
    QObject::connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(MainPosition()));
    QObject::connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(MainPosition()));
    QObject::connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(MainPosition()));
    QObject::connect(ui->radioButton_4, SIGNAL(clicked()), this, SLOT(MainPosition()));
    QObject::connect(ui->radioButton_5, SIGNAL(clicked()), this, SLOT(MainPosition()));
    QObject::connect(ui->radioButton_6, SIGNAL(clicked()), this, SLOT(SubPositon()));
    QObject::connect(ui->radioButton_7, SIGNAL(clicked()), this, SLOT(SubPositon()));
    QObject::connect(ui->radioButton_8, SIGNAL(clicked()), this, SLOT(SubPositon()));
    QObject::connect(ui->radioButton_9, SIGNAL(clicked()), this, SLOT(SubPositon()));
    QObject::connect(ui->radioButton_10, SIGNAL(clicked()), this, SLOT(SubPositon()));
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_OK_clicked()
{
    nickname = ui->lineEdit_lol_nickname->text().toUtf8();
    id = ui->lineEdit_id->text().toUtf8();
    pwd = ui->lineEdit_password->text().toUtf8();

    signuInfo.nickname = nickname.toLocal8Bit().constData();
    signuInfo.id = id.toLocal8Bit().constData();
    signuInfo.pwd = pwd.toLocal8Bit().constData();
    signuInfo.position1 = mainPosition.toLocal8Bit().constData();
    signuInfo.position2 = subPosition.toLocal8Bit().constData();

    signupSock->sendData(signuInfo);
    signupSuccess = signupSock->receiveData();

    if (signupSuccess) {
        QMessageBox::information(this,"Sing in","Sign in Complete");
        delete signupSock;
        close();
    }
    else {
        QMessageBox::information(this,"Sing in","Sign in Failed");
    }
}

void SignUp::MainPosition() {
    if (ui->radioButton->isChecked())
        mainPosition = ui->radioButton->text();
    if (ui->radioButton_2->isChecked())
        mainPosition = ui->radioButton->text();
    if (ui->radioButton_3->isChecked())
        mainPosition = ui->radioButton->text();
    if (ui->radioButton_4->isChecked())
        mainPosition = ui->radioButton->text();
    if (ui->radioButton_5->isChecked())
        mainPosition = ui->radioButton->text();
}

void SignUp::SubPositon() {
    if (ui->radioButton_6->isChecked())
        subPosition = ui->radioButton->text();
    if (ui->radioButton_7->isChecked())
        subPosition = ui->radioButton->text();
    if (ui->radioButton_8->isChecked())
        subPosition = ui->radioButton->text();
    if (ui->radioButton_9->isChecked())
        subPosition = ui->radioButton->text();
    if (ui->radioButton_10->isChecked())
        subPosition = ui->radioButton->text();
}
