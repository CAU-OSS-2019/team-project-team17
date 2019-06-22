#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>
#include "matching_client.h"
#include <fstream>
#include <Windows.h>
#include <ShlObj.h>
#include <tchar.h>
#include <QMessageBox>
#include <string>
#include <string.h>
#include <QClipboard>

namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    void SetUser(result_of_matching user);
    ~AddFriend();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddFriend *ui;
    result_of_matching userData;
};

#endif // ADDFRIEND_H
