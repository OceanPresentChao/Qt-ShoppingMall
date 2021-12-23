#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include<qjsonobject.h>
class Person
{
public:
    Person(QJsonObject);
    QString name;
    QString password;
    int getId();
private:
    int id;

};

#endif // PERSON_H
