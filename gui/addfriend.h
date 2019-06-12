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
    void SetUser(matched_user user);
    ~AddFriend();

private:
    Ui::AddFriend *ui;
    matched_user userData;
};

#endif // ADDFRIEND_H
