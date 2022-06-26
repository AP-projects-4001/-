#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data/model/user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(User user, QWidget *parent = nullptr);
    ~MainWindow();
    static User getUser();
    static int get_id_porject();
//    static User user;

signals:
    void send_id_project(int);
private slots:
    void on_logOutButton_clicked();

    void on_my_account_button_clicked();

    void on_my_project_button_clicked();

    void catch_id(int id);

    void on_add_member_button_clicked();

    void show_button();

private:
    Ui::MainWindow *ui;
    static User user;
    static int id_project;
};
#endif // MAINWINDOW_H
