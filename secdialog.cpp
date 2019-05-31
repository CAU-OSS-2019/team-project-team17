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

    running_state = true;
//    matchingSock = new MatchingSocketClient("matching socket", "13.209.15.157", 8888);
//    source.nickname = "뚱땡이버거";
//    matchingSock->sendData(source);

//    result = matchingSock->receiveData();

//    if((matchingSock->receive_success) == -1)
//        cout << "Failed" << endl;
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), Movie, SLOT(stop()));
    addf = new AddFriend();

}

void SecDialog::displayMatchedUserInfo() {
}
