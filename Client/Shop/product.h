#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>
#include<QJsonObject>
class Product
{
public:
    Product();
    Product(QJsonObject obj);
    int id;
    bool islimited;
    QString pictureaddress;
    QString name;
    QString about;
    QString classification;
    int price;
    int amount;
    int sales;
private:

};

#endif // PRODUCT_H
