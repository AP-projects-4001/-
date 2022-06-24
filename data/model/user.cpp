#include "user.h"
#include "../../utils/exception.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QThread>
#include <iostream>

using namespace std;

User::User() {
    this->name = "";
    this->username = "";
    this->password = "";
    this->email = "";
    this->phone_number = "";

}

User::User(QString name, QString username, QString password, QString email, QString phone_number, int id) {
    this->name = name;
    this->username = username;
    this->password = password;
    this->id =id;
    this->email = email;
    this->phone_number = phone_number;

}

QString User::get_name() {
    return this->name;

}

QString User::get_username() {
    return this->username;
}

QString User::get_password() {
    return this->password;
}

QString User::get_email() {
    return this->email;
}

QString User::get_phone_number() {
    return this->phone_number;
}

int User::get_id()
{
    return this->id;
}

QList <QString> User::get_projects_id() {
    return this->projects_id;
}

void User::set_name(QString name) {
    this->name = name;
}

void User::set_username(QString username) {
    this->username = username;
}

void User::set_password(QString password) {
    this->password = password;
}

void User::set_email(QString email) {
    this->email = email;
}

void User::set_phone_number(QString phone_number) {
    this->phone_number = phone_number;
}

void User::set_projects_id(QList <QString> projects_id) {
    this->projects_id = projects_id;
}

void User::set_id(int id)
{
    this->id = id;
}

QJsonObject User::toJsonObject() {
    QJsonObject res;
    QJsonArray projects_id;
    res["name"] = get_name();
    res["username"] = get_username();
    res["password"] = get_password();
    res["email"] = get_email();

    res["id"] = get_id();
    res["phone_number"] = get_phone_number();
    foreach(QString
    value, get_projects_id()) {
        projects_id.append(value);
    }
    res["projects_id"] = projects_id;

    return res;
}


