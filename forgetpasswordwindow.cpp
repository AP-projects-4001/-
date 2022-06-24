#include "forgetpasswordwindow.h"
#include "ui_forgetpasswordwindow.h"
#include "data/model/user.h"
#include "data/database/database.h"
#include <QMessageBox>
#include <QDebug>

ForgetPasswordWindow::ForgetPasswordWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ForgetPasswordWindow) {
    ui->setupUi(this);
}

ForgetPasswordWindow::~ForgetPasswordWindow() {
    delete ui;
}

void ForgetPasswordWindow::on_buttonBox_accepted() {
    User user;
    Database database;
    user = database.get_user(ui->username_line->text());

    if (ui->username_line->text() == "" || ui->newpassword_line->text() == "") {
        QMessageBox::information(this, tr("Warning"), tr("Please fill in all fields"));

    } else {
        if (user.get_username() != "") {
            user.set_password(ui->newpassword_line->text());
            database.edit_user(user.get_username(), user);

            emit signal_username(ui->username_line->text());
            emit signal_password(ui->newpassword_line->text());

            QMessageBox::information(this, "Success", "Changed Password");

        } else {
            QMessageBox::warning(this, "Error", "The Username Is Not Exist");
        }
    }


}
