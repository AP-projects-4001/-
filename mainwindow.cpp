#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/model/user.h"
#include "loginwindow.h"
#include "settingwindow.h"
#include "QDebug"
#include "projectswindow.h"
#include "QJsonArray"
#include "QString"
#include "addmemberwindow.h"
#include "data/database/database.h"

MainWindow::MainWindow(User user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->user = user;
    ui->setupUi(this);
    id_project = -1;


    if(id_project == -1) {
        ui->project_name->setStyleSheet("color: rgb(255,25,25)");
        ui->project_name->setText("No project selected");
        ui->your_position->setStyleSheet("color: rgb(255,25,25)");
        ui->your_position->setText("No Position");
        ui->add_task_button->setDisabled(true);
        ui->add_member_button->setDisabled(true);
        ui->chat_button->setDisabled(true);

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

int MainWindow::get_id_porject() {
    return id_project;
}

User MainWindow::user = User();

int MainWindow::id_project = -1;

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
     id_project = id;
     Database database;
     Project project = database.get_project_by_id(id);
     ui->project_name->setStyleSheet("color: rgb(0,0,0)");
     ui->project_name->setText(project.getName());
     ui->your_position->setStyleSheet("color: rgb(0,0,0)");
     ui->your_position->setText(database.find_position(user.get_id(), id));
     show_button();
}



void MainWindow::on_add_member_button_clicked()
{
    AddMemberWindow *amw = new AddMemberWindow(this);
    amw->show();

}

void MainWindow::show_button()
{
    Database database;

    if(database.find_position(user.get_id(), get_id_porject()) == "leader"
            || database.find_position(user.get_id(), get_id_porject()) == "elder"){
        ui->add_task_button->setEnabled(true);
        ui->add_member_button->setEnabled(true);
        ui->chat_button->setEnabled(true);

    }else{
        ui->chat_button->setEnabled(true);
    }

}


