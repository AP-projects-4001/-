#ifndef USER_H
#define USER_H

#include <QList>
#include <QJsonObject>
#include <QString>
#include<QObject>

class User
{

private:

    QString name;
    QString username;
    QString password;
    QString email;
    QString phone_number;
    QList<QString> projects_id;

public:
    User();

    User(    QString name,
    QString username,
    QString password,
    QString email,
    QString phone_number);

    QString get_name();
    QString get_username();
    QString get_password();
    QString get_email();
    QString get_phone_number();
    QList<QString> get_projects_id();

    void set_name(QString name);
    void set_username(QString username);
    void set_password(QString password);
    void set_email(QString email);
    void set_phone_number(QString phone_number);
    void set_projects_id(QList<QString> projects_id);

    QJsonArray get_users();
    void add_user(User user);
    User get_user(QString username);

    void edit_user(QString username, User user);
    QJsonObject toJsonObject();
};



#endif // USER_H
