#ifndef CARTPAGE_H
#define CARTPAGE_H

#include <QWidget>
#include "../Shop/product.h"
#include "cartitem.h"
#include<QMap>
#include<QMessageBox>
#include"../shoppingclient.h"
#include<QJsonArray>
#include<QJsonObject>
namespace Ui {
class CartPage;
}

class CartPage : public QWidget
{
    Q_OBJECT

public:
    explicit CartPage(QWidget *parent = nullptr);
    ~CartPage();
    void showEvent(QShowEvent *event);
    QMap<int,CartItem*> cartlist;//通过商品的pro_id来查找cartlist
    int tolprice;//购物车被选中商品的总金额
    ShoppingClient *client;

private:
    Ui::CartPage *ui;
    void loadCart();
    bool isCached;

public slots:
    void addToCart(Product*);//将商品加入购物车
    void updateCart(int pro_id,int num);//更新购物车商品数量
    void deleteCart(int pro_id);//删除购物车项
    void addChange(int);//购物车被选中项改变购物车总金额
    void buySth();//购买物品
    void updateCartMoney(int change);//购买后修改购物车总金额
signals:
    void signal_updateUserMoney(int);
    void signal_updateCartMoney(int);

};

#endif // CARTPAGE_H
