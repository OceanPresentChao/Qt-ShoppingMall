#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <QWidget>
#include"orderitem.h"
#include<QJsonArray>
#include<QJsonObject>
#include"./shoppingclient.h"
#include<QStringList>
#include<QListWidgetItem>
#include<QMap>
namespace Ui {
class OrderPage;
}

class OrderPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);
    OrderPage(QJsonArray arr);
    ~OrderPage();
    ShoppingClient *client;
    QStringList statuslist;
    QMap<QString,QJsonObject> orderlist;
    void addItem(OrderItem* item);
    void setStatus(QString status);
    void setPrice(QString price);


private:
    Ui::OrderPage *ui;
    int current;
    void showEvent(QShowEvent *event);
    void getAllOrder();
    void updateOrderItems(QString ordernum);

private slots:
    void nextOrder();
    void backOrder();
};

#endif // ORDERPAGE_H
