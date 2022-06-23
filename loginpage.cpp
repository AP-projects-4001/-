#include "loginpage.h"
#include "ui_loginpage.h"
#include "user.cpp"
#include "createaccountwindow.h"
#include "forgetpasswordwindow.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>

using namespace std;

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}






void LoginPage::on_create_account_button_clicked()
{
    CreateAccountWindow *caw = new CreateAccountWindow(this);

    caw->show();

    connect(caw, SIGNAL(signal_username(QString)), this, SLOT(fill_username(QString)));
    connect(caw, SIGNAL(signal_password(QString)), this, SLOT(fill_password(QString)));
}



void LoginPage::on_login_button_clicked()
{




        if(ui->set_username->text() == "" || ui->set_pasword->text() == ""){
            QMessageBox::warning(this, tr("Warning"), tr("Please fill in all fields"));
        }else{
            User user;
            user = user.get_user(ui->set_username->text());

            if(user.get_username() != ""){
                   if(user.get_password() == ui->set_pasword->text()){
//                       QMessageBox::information(this, tr("Warning"), tr("login"));
                       MainWindow *mw = new MainWindow();
                       mw->show();
                       LoginPage::close();
                   }else{
                       QMessageBox::warning(this, tr("Warning"), tr("Wrong Password"));
                   }

            }else{
                QMessageBox::warning(this, tr("Warning"), tr("Username Is Not Exists"));
            }

        }


}



void LoginPage::on_forget_password_Button_clicked()
{
    ForgetPasswordWindow *fpw = new ForgetPasswordWindow();

    fpw->show();

    connect(fpw, SIGNAL(signal_username(QString)), this, SLOT(fill_username(QString)));
    connect(fpw, SIGNAL(signal_password(QString)), this, SLOT(fill_password(QString)));
}

void LoginPage::fill_username(QString str_user)
{
    ui->set_username->setText(str_user);
}

void LoginPage::fill_password(QString str_pass)
{
 ui->set_pasword->setText(str_pass);
}
