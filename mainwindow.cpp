#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/model/user.h"
#include "loginwindow.h"
#include "settingwindow.h"
#include "QDebug"

MainWindow::MainWindow(User user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->user = user;
    ui->setupUi(this);
    if(user.get_projects_id().size() == 0) {
        ui->project_name->setStyleSheet("color: rgb(255,25,25)");
        ui->project_name->setText("no project selected");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

User MainWindow::getUser()
{
    return user;
}



User MainWindow::user = User();


void MainWindow::on_logOutButton_clicked()
{
    LoginWindow *loginWindow = new LoginWindow();

    loginWindow->show();
    MainWindow::close();
}

void MainWindow::on_my_account_button_clicked()
{
    SettingWindow *sw = new SettingWindow(this);

    sw->show();
}
