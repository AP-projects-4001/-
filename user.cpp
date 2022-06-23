#include "user.h"
#include "exception.cpp"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QThread>
#include <iostream>

using namespace std;

User::User()
{
    this->name = "";
    this->username = "";
    this->password = "";
    this->email = "";
    this->phone_number = "";

}

User::User(QString name, QString username, QString password, QString email, QString phone_number)
{
    this->name = name;
    this->username = username;
    this->password = password;
    this->email = email;
    this->phone_number = phone_number;

}

QString User::get_name()
{
    return this->name;

}

QString User::get_username()
{
    return this->username;
}

QString User::get_password()
{
    return this->password;
}

QString User::get_email()
{
    return this->email;
}

QString User::get_phone_number()
{
    return this->phone_number;
}

QList<QString> User::get_projects_id()
{
    return this->projects_id;
}

void User::set_name(QString name)
{
    this->name = name;
}

void User::set_username(QString username)
{
    this->username = username;
}

void User::set_password(QString password)
{
    this->password = password;
}

void User::set_email(QString email)
{
    this->email = email;
}

void User::set_phone_number(QString phone_number)
{
    this->phone_number = phone_number;
}

void User::set_projects_id(QList<QString> projects_id)
{
    this->projects_id = projects_id;
}


User User::get_user(QString username) {

    QJsonArray users = get_users();

    foreach (QJsonValue value, users) {
       if(value["username"] == username)
           return User(value["name"].toString(),value["username"].toString(),value["password"].toString(),value["email"].toString(),value["phone_number"].toString());
    }

    return User();
}

void User::edit_user(QString username, User user)
{
    QJsonArray users = get_users();
    int index = 0;

    foreach (QJsonValue value, users) {
        if(value["username"].toString() == username){
            users.replace(index,user.toJsonObject());
            break;
        }
        index += 1;
    }
   QFile DBW("C:\\Users\\Mohsen\\Documents\\ProjectManagement\\Users.json");
   DBW.open(QIODevice::WriteOnly);
   QJsonObject result;
   result["Users"] = users;
   DBW.write(QJsonDocument(result).toJson());

   DBW.close();
}

void User::add_user(User user)
{
    if (user.get_username() == get_user(user.get_username()).get_username()){
        throw Exception(0,"username is exists");
    }

    QJsonArray users = get_users();
    QJsonObject result;
    users.append(user.toJsonObject());
    result["Users"] = users;
    QJsonDocument doc_user(result);
     QFile DBW("C:\\Users\\Mohsen\\Documents\\ProjectManagement\\Users.json");
      DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_user.toJson());

    DBW.close();
}

QJsonObject User::toJsonObject()
{
    QJsonObject res;
    QJsonArray projects_id;
    res["name"] = get_name();
    res["username"] = get_username();
    res["password"] = get_password();
    res["email"] = get_email();
    res["phone_number"] = get_phone_number();
    foreach (QString value, get_projects_id()) {
        projects_id.append(value);
    }
    res["projects_id"]=projects_id;

    return res;
}

QJsonArray User::get_users()
{

    QFile DBR("C:\\Users\\Mohsen\\Documents\\ProjectManagement\\Users.json");
    DBR.open(QIODevice::ReadOnly);

    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    QJsonArray res = qjo["Users"].toArray();

    DBR.close();

    return res;

}


