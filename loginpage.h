#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void fill_username(QString str_user);
    void fill_password(QString str_pass);

    void on_create_account_button_clicked();

    void on_login_button_clicked();


    void on_forget_password_Button_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
