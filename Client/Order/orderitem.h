#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QWidget>
#include<QJsonArray>
#include<QJsonObject>
namespace Ui {
class OrderItem;
}

class OrderItem : public QWidget
{
    Q_OBJECT

public:
    OrderItem(QJsonObject obj);
    ~OrderItem();
    void setProname(QString name);
    void setPicture(QString url);
    void setPronum(QString num);
    void setProprice(QString price);
    void setProtolprice(QString tolprice);

private:
    Ui::OrderItem *ui;
};

#endif // ORDERITEM_H
