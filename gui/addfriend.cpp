#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::SetUser(result_of_matching user) {
    userData = user;
    ui->textEdit->append(user.duonickname);
    ui->textEdit->append(user.duorank);
    ui->textEdit->append("Conformity");
    ui->textEdit->append(to_string(user.conformity).c_str());
}

void AddFriend::on_pushButton_clicked()
{
    this->close();
}

void AddFriend::on_pushButton_2_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString text = userData.duonickname;
    clipboard->setText(text);

    if (IsUserAnAdmin() == FALSE) {
        SHELLEXECUTEINFO si;
        ZeroMemory(&si, sizeof(SHELLEXECUTEINFO));

        si.cbSize = sizeof(SHELLEXECUTEINFO);
        si.hwnd = NULL;
        si.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
        si.lpVerb = _T("runas");
        si.lpFile = _T("C:/test/Verification/add_friend_macro/addfriend.exe");
        si.nShow = SW_SHOWNORMAL;
        si.lpDirectory = NULL;
        ShellExecuteEx(&si);
    }

    this->close();
}
