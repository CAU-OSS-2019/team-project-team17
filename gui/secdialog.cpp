#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    QMovie *Movie=new QMovie(":/img/loading2.gif");
    ui->label_2->setMovie(Movie);
    Movie->start();

    char buf[1024] = "13.209.7.127";
    running_state = true;
    matchingSock = new MatchingSocketClient("matching socket", buf, 9000);
    matchingSock->sendData(source);

    match_success = matchingSock->receiveWaitData();
    while(!match_success){
        cout <<"---Wait---" <<endl;
        matchingSock->sendData(source);
        match_success = matchingSock->receiveWaitData();
    }

    result = matchingSock->receiveMatchingData();

    if((matchingSock->receive_success) == -1) {
        cout << "Failed" << endl;
    }
    else {
        delete matchingSock;
        Movie->stop();
        ui->label_2->clear();
        displayMatchedUserInfo();
    }
}

void SecDialog::displayMatchedUserInfo()
{
    addf = new AddFriend();

}

void SecDialog::setData(login_data user) {
    userData = user;
}
