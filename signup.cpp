#include "signup.h"
#include "ui_signup.h"

#include <QMessageBox>

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
    QString lol_nickname = ui->lineEdit_lol_nickname->text();
    QString id = ui->lineEdit_id->text();
    QString pw = ui->lineEdit_password->text();


    QMessageBox::information(this,"Sing in","Sign in Complete");
    close();
}


