#ifndef DATABASE_H
#define DATABASE_H
#include "..\model\user.h"

class Database
{
public:
    Database();

    QJsonArray get_users();
    void add_user(User user);
    User get_user(QString username);
    User get_user_by_id(int id);

    void edit_user(QString username, User user);
    void edit_user_by_id(int id, User user);
};

#endif // DATABASE_H
