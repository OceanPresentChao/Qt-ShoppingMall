#include "person.h"

Person::Person(QJsonObject obj)
{
    int _id = obj.value("manager_id").toString().toInt();
    QString _name = obj.value("manager_name").toString();
    QString _password = obj.value("manager_password").toString();
    this->id = _id;
    this->name = _name;
    this->password = _password;

}

int Person::getId(){
    return this->id;
}

