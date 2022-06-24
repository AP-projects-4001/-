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
//    static User user;

private slots:
    void on_logOutButton_clicked();

    void on_my_account_button_clicked();

    void on_my_project_button_clicked();

    void catch_id(int id);

    void on_add_member_button_clicked();

private:
    Ui::MainWindow *ui;
    static User user;
};
#endif // MAINWINDOW_H
