#include "createaccountwindow.h"
#include "ui_createaccountwindow.h"
#include "user.h"
#include "exception.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QThread>



CreateAccountWindow::CreateAccountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccountWindow)
{
    ui->setupUi(this);
}

CreateAccountWindow::~CreateAccountWindow()
{
    delete ui;
}




void CreateAccountWindow::on_create_button_clicked()
{

        if(ui->input_name->text() == ""){
            QMessageBox::information(this, tr("Warning"), tr("The Name Is Null!"));
        }
        else if (ui->input_username->text() == "")
        {
            QMessageBox::information(this, tr("Warning"), tr("The Username Is Null!"));
        }
        else if(ui->input_password->text() == "")
        {
            QMessageBox::information(this, tr("Warning"), tr("The Password Is Null!"));
        }
        else if(ui->input_email->text() == "")
        {
            QMessageBox::information(this, tr("Warning"), tr("The Email Is Null!"));
        }
        else if(ui->input_phone_number->text() == "")
        {
            QMessageBox::information(this, tr("Warning"), tr("The Phone Number Is Null!"));
        } else {
            User user;
            user.set_name(ui->input_name->text());
            user.set_username(ui->input_username->text());
            user.set_password(ui->input_password->text());
            user.set_email(ui->input_email->text());
            user.set_phone_number(ui->input_phone_number->text());
        try {

            user.add_user(user);
            QMessageBox::information(this, tr("Warning"), tr("Account Created Successfully"));


            emit signal_username(ui->input_username->text());
            emit signal_password(ui->input_password->text());


            CreateAccountWindow::on_exitBtn_clicked();

        } catch (Exception e) {
                QMessageBox::information(this, tr("Warning"), e.get_message());
        }


  }





}




void CreateAccountWindow::on_exitBtn_clicked()
{
    CreateAccountWindow::close();
}

