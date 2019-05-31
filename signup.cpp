#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
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
    signupSock = new SignupSocketClient("signup socket", "13.209.15.157", 8888);
    nickname = ui->lineEdit_lol_nickname->text().toUtf8();
    id = ui->lineEdit_id->text().toUtf8();
    pwd = ui->lineEdit_password->text().toUtf8();

    signuInfo.nickname = nickname.toLocal8Bit().constData();
    signuInfo.id = id.toLocal8Bit().constData();
    signuInfo.pwd = pwd.toLocal8Bit().constData();
    //signuInfo.position1 = mainPosition.toLocal8Bit().constData();
    //signuInfo.position2 = subPosition.toLocal8Bit().constData();

    QMessageBox Msgbox;

    if (nickname.isEmpty() || id.isEmpty() || pwd.isEmpty() || mainPosition.isEmpty() || subPosition.isEmpty())
    {
        Msgbox.setText("Please write without blank");
        Msgbox.exec();
    }
    else
    {
        signupSock->sendData(signuInfo);
        if (signupSock->send_success == -1)
        {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
        }
        else
        {
            signupSuccess = signupSock->receiveData();
            if (signupSuccess)
            {
                Msgbox.setText("Sign in Complete");
                Msgbox.exec();
                delete signupSock;
                close();
            }
            else
            {
                if (signupSock->receive_success == -1)
                {
                    Msgbox.setText("Sever Error");
                    Msgbox.exec();
                }
                else
                {
                Msgbox.setText("Sign in Failed");
                Msgbox.exec();
                }
            }
        }
    }
}

void SignUp::MainPosition()
{
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

void SignUp::SubPositon()
{
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


