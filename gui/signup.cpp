#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_OK_clicked()
{
    char buf[1024] = "13.125.138.196";
    signupSock = new SignupSocketClient("signup socket", buf, 9200);
    nickname = ui->lineEdit_lol_nickname->text().toUtf8();
    id = ui->lineEdit_id->text().toUtf8();
    pwd = ui->lineEdit_password->text().toUtf8();

    strncpy(signuInfo.nickname, nickname.toUtf8().constData(), sizeof(signuInfo.nickname));
    strncpy(signuInfo.id, id.toLocal8Bit().constData(), sizeof(signuInfo.id));
    strncpy(signuInfo.pwd, pwd.toLocal8Bit().constData(), sizeof(signuInfo.pwd));


    QMessageBox Msgbox;

    if (nickname.isEmpty() || id.isEmpty() || pwd.isEmpty()) {
        Msgbox.setText("Please write without blank");
        Msgbox.exec();
    } else {
        signupSock->sendData(signuInfo);
        if (signupSock->send_success == -1) {
            Msgbox.setText("Send Data Failed");
            Msgbox.exec();
        } else {
            signupSuccess = signupSock->receiveData();
            if (signupSuccess) {
                Msgbox.setText("Sign up Complete");
                Msgbox.exec();
                delete signupSock;
                close();
            } else {
                if (signupSock->receive_success == -1) {
                    Msgbox.setText("Sever Error");
                    Msgbox.exec();
                } else {
                Msgbox.setText("Sign up Failed");
                Msgbox.exec();
                }
            }
        }
    }
}

void SignUp::on_pushButton_3_clicked()
{
    STARTUPINFO StartupInfo = {0};

    StartupInfo.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION ProcessInfo;

    //LPWSTR wstr = L"C:/test/req/team-project-team17/authenticate/checknick.exe";

   // ::CreateProcess(wstr, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);

    if (IsUserAnAdmin() == FALSE) {
        SHELLEXECUTEINFO si;
        ZeroMemory(&si, sizeof(SHELLEXECUTEINFO));

        si.cbSize = sizeof(SHELLEXECUTEINFO);
        si.hwnd = NULL;
        si.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
        si.lpVerb = _T("runas");
        si.lpFile = _T("C:/test/Verification/authenticate/checknick.exe");
        si.nShow = SW_SHOWNORMAL;
        si.lpDirectory = NULL;
        ShellExecuteEx(&si);
    }



    Sleep(5000);
    QMessageBox Msgbox;

    ifstream read;
    read.open("C:/test/Verification/authenticate/nick.txt");

    string nickn;
    read >> nickn;
    nickname = ui->lineEdit_lol_nickname->text().toUtf8();
    string str = nickname.toUtf8().constData();

    if (nickn == str) {
        Msgbox.setText("Authentication complete");
        Msgbox.exec();

    }
    else {
        Msgbox.setText("Not You");
        Msgbox.exec();
        cout << nickn << endl;
        cout << str << endl;
    }
}
