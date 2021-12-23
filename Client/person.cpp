#include "person.h"

Person::Person(QJsonObject obj)
{
    int _id = obj.value("user_id").toString().toInt();
    int _money = obj.value("user_money").toString().toInt();
    QString _name = obj.value("user_name").toString();
    QString _password = obj.value("user_password").toString();
    QString _address = obj.value("user_address").toString();
    QString _gender = obj.value("user_gender").toString();
    this->id = _id;
    this->name = _name;
    this->password = _password;
    this->address = _address;
    this->money = _money;
    this->gender = _gender;
}

int Person::getId(){
    return this->id;
}

int Person::getmoney(){
    return this->money;
}

void Person::setmoney(int num){
    this->money = num;
}
