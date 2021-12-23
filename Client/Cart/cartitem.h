#ifndef CARTITEM_H
#define CARTITEM_H

#include <QWidget>
#include<QMouseEvent>
#include<QAction>
#include<QMenu>
#include<QListWidgetItem>
#include"../Shop/product.h"
#include"../person.h"
namespace Ui {
class CartItem;
}

class CartItem : public QWidget
{
    Q_OBJECT

public:
    CartItem(int pro_id,QString pro_address,QString pro_name,int pro_price,int tolprice,int initnum);
    ~CartItem();
    void setPicture(QString url);
    void setSpinNum(int num);
    int getSpinNum();
    int getprice();
    int getProId();
    bool getChecked();
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void refreshMax(int maxnum);
    int num;
    int tolprice;//某一商品的总价
    QListWidgetItem *widgetitem;

private:
    Ui::CartItem *ui;
    int price;
    int pro_id;


signals:
    void signal_checkedchanged(int num);
    void signal_valchanged(int pro_id,int num);
    void signal_delItem(int pro_id);

private slots:
    void setChecked();
    void valChanged(int num);
};

#endif // NEWCOURIERITEM_H
