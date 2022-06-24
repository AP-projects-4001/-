#include "database.h"
#include "../../utils/exception.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QThread>
#include <iostream>

Database::Database()
{

}


User Database::get_user(QString username) {

    QJsonArray users = get_users();

    foreach(QJsonValue
    value, users) {
        if (value["username"] == username)
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                    value["email"].toString(), value["phone_number"].toString(), value["id"].toInt());
    }

    return User();
}

User Database::get_user_by_id(int id)
{
    QJsonArray users = get_users();

    foreach(QJsonValue
    value, users) {
        if (value["id"] == id)
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                        value["email"].toString(), value["phone_number"].toString(), value["id"].toInt());
    }

    return User();
}

void Database::edit_user(QString username, User user) {
    QJsonArray users = get_users();
    int index = 0;

    foreach(QJsonValue
    value, users) {
        if (value["username"].toString() == username) {
            users.replace(index, user.toJsonObject());
            break;
        }
        index += 1;
    }
    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    QJsonObject result;
    result["Users"] = users;
    DBW.write(QJsonDocument(result).toJson());

    DBW.close();
}

void Database::edit_user_by_id(int id, User user)
{
    qDebug() << id << "------" << get_user(user.get_username()).get_id();
    if (user.get_username() == get_user(user.get_username()).get_username()
            && id != get_user(user.get_username()).get_id()) {
        throw Exception(0, "username is exists");
    }

    QJsonArray users = get_users();


    users.replace(id, user.toJsonObject());

    qDebug() << user.toJsonObject();

    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    QJsonObject result;
    result["Users"] = users;
    qDebug() << result;
    DBW.write(QJsonDocument(result).toJson());

    DBW.close();

}

void Database::add_user(User user) {
    if (user.get_username() == get_user(user.get_username()).get_username()) {
        throw Exception(0, "username is exists");
    }

    QJsonArray users = get_users();
    QJsonObject result;
    user.set_id(users.size());
    users.append(user.toJsonObject());
    result["Users"] = users;

    QJsonDocument doc_user(result);
    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_user.toJson());

    DBW.close();
}

QJsonArray Database::get_users() {

    QFile DBR("Users.json");
    DBR.open(QIODevice::ReadOnly);

    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    QJsonArray res = qjo["Users"].toArray();

    DBR.close();

    return res;

}
