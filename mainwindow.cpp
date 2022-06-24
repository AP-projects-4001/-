#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/model/user.h"
#include "loginwindow.h"
#include "settingwindow.h"
#include "QDebug"
#include "projectswindow.h"
#include "QJsonArray"

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

void MainWindow::on_my_project_button_clicked()
{
    ProjectsWindow *projectsWindow = new ProjectsWindow();
    projectsWindow->show();

    connect(projectsWindow, SIGNAL(send_project_id(int)), this, SLOT(catch_id(int)));


}

void MainWindow::catch_id(int id)
{

}



void MainWindow::on_add_member_button_clicked()
{

}
