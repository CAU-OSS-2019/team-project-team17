#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->Top1, SIGNAL(clicked()), this, SLOT(MyPosition()));
    QObject::connect(ui->Top2, SIGNAL(clicked()), this, SLOT(ProperPosition()));
    QObject::connect(ui->Mid1, SIGNAL(clicked()), this, SLOT(MyPosition()));
    QObject::connect(ui->Mid2, SIGNAL(clicked()), this, SLOT(ProperPosition()));
    QObject::connect(ui->Jungle1, SIGNAL(clicked()), this, SLOT(MyPosition()));
    QObject::connect(ui->Jungle2, SIGNAL(clicked()), this, SLOT(ProperPosition()));
    QObject::connect(ui->AD1, SIGNAL(clicked()), this, SLOT(MyPosition()));
    QObject::connect(ui->AD2, SIGNAL(clicked()), this, SLOT(ProperPosition()));
    QObject::connect(ui->Suppot1, SIGNAL(clicked()), this, SLOT(MyPosition()));
    QObject::connect(ui->Suppot2, SIGNAL(clicked()), this, SLOT(ProperPosition()));
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

    if (mypos.isEmpty() || propos.isEmpty()) {
        Msgbox.setText("Please Check Position");
        Msgbox.exec();
    } else {
        char buf[1024] = "13.209.7.127";
        running_state = true;
        matchingSock = new MatchingSocketClient("matching socket", buf, 9000);
        matchingSock->sendData(source);
        if (matchingSock->send_success) {
            match_success = matchingSock->receiveWaitData();
            while(!match_success){
                cout <<"---Wait---" <<endl;
                matchingSock->sendData(source);
                match_success = matchingSock->receiveWaitData();
            }

            user = matchingSock->receiveMatchedUser();

            if((matchingSock->receive_success) == -1) {
                Msgbox.setText("Receive Failed");
                Msgbox.exec();
            }
            else {
                delete matchingSock;
                Movie->stop();
                ui->label_2->clear();
                displayMatchedUserInfo();
            }
        } else {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
        }
    }
}

void SecDialog::displayMatchedUserInfo()
{
    addf = new AddFriend();
    addf->SetUser(user);
    addf->show();
}

void SecDialog::setData(login_data user) {
    userData = user;
    ui->label->clear();
    ui->label->setText(userData.nickname);
    ui->label_3->clear();
    ui->label_3->setText(userData.rank);
}

void SecDialog::MyPosition() {
    if (ui->AD1->isChecked())
        mypos = ui->AD1->text();
    if (ui->Mid1->isChecked())
        mypos = ui->Mid1->text();
    if (ui->Top1->isChecked())
        mypos = ui->Top1->text();
    if (ui->Jungle1->isChecked())
        mypos = ui->Jungle1->text();
    if (ui->Suppot1->isChecked())
        mypos = ui->Suppot1->text();

    strcpy(source.myposition, mypos.toLocal8Bit().constData());
}

void SecDialog::ProperPosition() {
    if (ui->AD2->isChecked())
        propos = ui->AD2->text();
    if (ui->Mid2->isChecked())
        propos = ui->Mid2->text();
    if (ui->Top2->isChecked())
        propos = ui->Top2->text();
    if (ui->Jungle2->isChecked())
        propos = ui->Jungle2->text();
    if (ui->Suppot2->isChecked())
        propos = ui->Suppot2->text();

    strcpy(source.duoposition, propos.toLocal8Bit());
}
