#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QMovie>
#include <QPropertyAnimation>
#include "addfriend.h"
#include "matching_client.h"

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
    void displayMatchedUserInfo();

private:
    Ui::SecDialog *ui;
    AddFriend *addf;
    MatchingSocketClient *matchingSock;
    source_of_matching source;
    result_of_matching result;
    bool running_state = false;

};

#endif // SECDIALOG_H
