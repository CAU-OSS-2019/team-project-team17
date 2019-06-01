#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>
#include "matching_client.h"

namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();

private:
    Ui::AddFriend *ui;
    result_of_matching result;
};

#endif // ADDFRIEND_H
