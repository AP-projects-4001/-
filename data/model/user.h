#ifndef USER_H
#define USER_H

#include <QJsonArray>
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
    int id;
    QJsonArray projects_id;

public:
    User();

    User(    QString name,
    QString username,
    QString password,
    QString email,
    QString phone_number,
    int id,
             QJsonArray projects_id);

    QString get_name();
    QString get_username();
    QString get_password();
    QString get_email();
    QString get_phone_number();
    int get_id();
    QJsonArray get_projects_id();

    void set_name(QString name);
    void set_username(QString username);
    void set_password(QString password);
    void set_email(QString email);
    void set_phone_number(QString phone_number);
    void set_projects_id(QJsonArray projects_id);
    void set_id(int id);
    QJsonObject toJsonObject();
};



#endif // USER_H
