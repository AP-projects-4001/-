#ifndef DATABASE_H
#define DATABASE_H

#include "..\model\user.h"
#include "..\model\project.h"
#include "data/model/task.h"

class Database {
public:
    Database();

    // user table
    QJsonArray get_users();

    void add_user(User user);

    User get_user(QString username);

    User get_user_by_id(int id);

    void edit_user(QString username, User user);

    void edit_user_by_id(int id, User user);

    void add_project_to_user(int user_id, int project_id);

    // project table
    void add_project(Project project, int user_id);

    QJsonArray get_projects();

    QJsonArray get_projet_of_user(int user_id);

    QJsonArray get_my_team(int id_team);

    void add_member_to_project(int user_id, QString position, int id_project);

    Project get_project_by_id(int id);

    void edit_project_by_id(Project project, int id);

    QString find_position(int user_id, int id_project);

    // task table
    void add_task(Task task);

    QJsonArray get_tasks();

    void edit_task_by_id(int id_task);

    int get_last_id_of_task();

    void edit_task_by_id(int id, Task task);

    void delete_task(int id);

};

#endif // DATABASE_H
