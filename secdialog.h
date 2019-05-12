#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QPropertyAnimation>
#include "addfriend.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecDialog *ui;
    AddFriend *addf;
};

#endif // SECDIALOG_H
