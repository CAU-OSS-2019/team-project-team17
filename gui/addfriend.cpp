#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::SetUser(matched_user user) {
    userData = user;
    ui->textEdit->append(user.res2.duonickname);
    ui->textEdit->append(user.res2.duorank);
}
