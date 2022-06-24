#ifndef DATABASE_H
#define DATABASE_H
#include "..\model\user.h"
#include "..\model\project.h"
class Database
{
public:
    Database();

    // user table
    QJsonArray get_users();
    void add_user(User user);
    User get_user(QString username);
    User get_user_by_id(int id);
    void edit_user(QString username, User user);
    void edit_user_by_id(int id, User user);
    void add_project_to_user(int user_id,int project_id);

    // project table
    void add_project(Project project, int user_id);
    QJsonArray get_projects();
    QJsonArray get_projet_of_user(int user_id);
};

#endif // DATABASE_H
