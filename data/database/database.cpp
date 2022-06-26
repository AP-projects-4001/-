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
#include "mainwindow.h"
#include <QMessageBox>
#include "addmemberwindow.h"

Database::Database() {

}


User Database::get_user(QString username) {

    QJsonArray users = get_users();

    foreach(QJsonValue value, users) {
        if (value["username"] == username)
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                        value["email"].toString(), value["phone_number"].toString(), value["id"].toInt(),value["projects_id"].toArray());
    }

    return User();
}

User Database::get_user_by_id(int id) {
    QJsonArray users = get_users();

    foreach(QJsonValue value, users) {
        if (value["id"].toInt() == id) {
            return User(value["name"].toString(), value["username"].toString(), value["password"].toString(),
                        value["email"].toString(), value["phone_number"].toString(), value["id"].toInt(),value["projects_id"].toArray());
        }
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

void Database::edit_user_by_id(int id, User user) {

    if (user.get_username() == get_user(user.get_username()).get_username()
        && id != get_user(user.get_username()).get_id()) {
        throw Exception(0, "username is exists");
    }

    QJsonArray users = get_users();


    users.replace(id, user.toJsonObject());

    QFile DBW("Users.json");
    DBW.open(QIODevice::WriteOnly);
    QJsonObject result;
    result["Users"] = users;
    DBW.write(QJsonDocument(result).toJson());

    DBW.close();

}

void Database::add_project_to_user(int user_id, int project_id)
{
    User user = get_user_by_id(user_id);
    QJsonArray projects_id = user.get_projects_id();
    projects_id.append(project_id);
    user.set_projects_id(projects_id);
    edit_user_by_id(user.get_id(),user);
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

void Database::add_project(Project project, int user_id) {
    QJsonArray projects = get_projects();
    QJsonObject result;
    project.setId(projects.size());
    QJsonArray members = project.getMembers();
    QJsonObject newMember;
    newMember["user_id"] = user_id;
    newMember["position"] = "leader";
    newMember["tasks_id"] = QJsonArray();
    members.append(newMember);
    project.setMembers(members);
    projects.append(project.toJsonObject());
    result["Projects"] = projects;

    add_project_to_user(user_id,project.getId());

    QJsonDocument doc_projects(result);

    QFile DBW("Projects.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());

    DBW.close();
}

QJsonArray Database::get_projects() {
    QFile DBR("Projects.json");
    DBR.open(QIODevice::ReadOnly);

    QByteArray qba = DBR.readAll();
    QJsonDocument qjd = QJsonDocument::fromJson(qba);
    QJsonObject qjo = qjd.object();
    QJsonArray res = qjo["Projects"].toArray();

    DBR.close();

    return res;
}

QJsonArray Database::get_projet_of_user(int user_id)
{
   QJsonArray projects = get_projects();
   QJsonArray filterdProjects;
   foreach (QJsonValue value, projects) {
       QJsonArray members = value["members"].toArray();
       foreach (QJsonValue value2, members) {
           if(value2["user_id"] == user_id) {
               filterdProjects.append(value);
           }
       }
   }
   return filterdProjects;
}

QJsonArray Database::get_my_team(int id_team)
{
    Project project = get_project_by_id(id_team);
    QJsonArray result;
    foreach (QJsonValue value, project.getMembers()) {
        User user = get_user_by_id(value["user_id"].toInt());
        user.set_position(value["position"].toString());
        result.append(user.toJsonObject());
    }
    return result;
}

void Database::add_member_to_project(int user_id, QString position, int id_project)
{
    Project project = get_project_by_id(id_project);
    QJsonObject newMember;
    foreach (QJsonValue value, project.getMembers()) {
        if(value["user_id"] == user_id)
            return;
    }
    newMember["position"] = position;
    newMember["tasks_id"] = QJsonArray();
    newMember["user_id"] = user_id;
    project.getMembers().append(newMember);
    edit_project_by_id(project,id_project);
}

Project Database::get_project_by_id(int id)
{
    QJsonArray projects = get_projects();
    QJsonValue value = projects[id];
    return Project(value["id"].toInt(),value["name"].toString(),value["members"].toArray());
}

void Database::edit_project_by_id(Project project, int id)
{
    QJsonArray projects = get_projects();
    projects.replace(id,project.toJsonObject());
    QJsonObject result;

    result["Projects"] = projects;

    QJsonDocument doc_projects(result);

    QFile DBW("Projects.json");
    DBW.open(QIODevice::WriteOnly);
    DBW.write(doc_projects.toJson());

    DBW.close();
}

QString Database::find_position(int user_id, int id_project)
{
    QString position;
    Project project = get_project_by_id(id_project);
    foreach (QJsonValue value, project.getMembers()) {
        if (value["user_id"].toInt() == user_id)
        {
            position =  value["position"].toString();

            break;
        }
    }
    return position;
}


