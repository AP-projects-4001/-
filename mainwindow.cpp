#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data/model/user.h"
#include "loginwindow.h"

MainWindow::MainWindow(User user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->user = user;
    ui->setupUi(this);
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
