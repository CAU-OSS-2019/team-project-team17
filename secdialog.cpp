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
    QWidget *b = new QWidget;
    b->setWindowTitle("Loading");
    b->setGeometry(400, 300, 120, 90);
    QHBoxLayout *layout = new QHBoxLayout();
    QProgressBar *bar = new QProgressBar();
    QPropertyAnimation *a = new QPropertyAnimation(bar, "value");
    a->setEasingCurve(QEasingCurve(QEasingCurve::OutQuad));
    a->setStartValue(0);
    a->setEndValue(100);
    a->setDuration(2000);
    a->start();
    layout->addWidget(bar);
    b->setLayout(layout);
    b->show();
    QObject::connect(a,SIGNAL(finished()), b, SLOT(hide()));

    addf = new AddFriend();
    QObject::connect(a,SIGNAL(finished()), addf, SLOT(show()));
}
