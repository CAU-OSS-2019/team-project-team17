#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
//    matchingSock = new MatchingSocketClient("matching socket", "13.209.15.157", 8888);
    ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    running_state = true;
//    source.nickname = "뚱땡이버거";
//    matchingSock->sendData(source);

//    result = matchingSock->receiveData();

//    if((matchingSock->receive_success) == -1)
//        cout << "Failed" << endl;
    QMovie *Movie=new QMovie(":/img/loading.gif");
    ui->label->setMovie(Movie);
    Movie->start();
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), Movie, SLOT(stop()));
    addf = new AddFriend();

}

void SecDialog::displayMatchedUserInfo() {
    cout << "data1 : " << result.data1 << "  "
                    << " data2 :  " << result.data2 << "  " << "data3 : "<<result.data3 << "  " << endl;
}
