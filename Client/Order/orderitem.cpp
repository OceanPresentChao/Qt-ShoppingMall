#include "orderitem.h"
#include "ui_orderitem.h"

OrderItem::OrderItem(QJsonObject obj) :
    ui(new Ui::OrderItem)
{
    ui->setupUi(this);
    if(obj.contains("pro_name")){
        setProname(obj.value("pro_name").toString());
    }
    if(obj.contains("pro_pictureaddress")){
        setPicture(obj.value("pro_pictureaddress").toString());
    }
    if(obj.contains("orderitem_num")){
        setPronum(obj.value("orderitem_num").toString());
    }
    if(obj.contains("orderitem_pro_price")){
        setProprice(obj.value("orderitem_pro_price").toString());
    }
    if(obj.contains("orderitem_tolprice")){
        setProtolprice(obj.value("orderitem_tolprice").toString());
    }
}

OrderItem::~OrderItem()
{
    delete ui;
}


void OrderItem::setPicture(QString url){
    QString add = ":/images/products/";
    QPixmap pixmap(add+url);
    if(pixmap.isNull()){
        add += "picerror.jpg";
    }
    else{
        add += url;
    }
   QString str = "QWidget{border-image:url("+add+");}";
   ui->widget->setStyleSheet(str);
}

void OrderItem::setProname(QString name){
    ui->lab_name->setText(name);
}

void OrderItem::setPronum(QString num){
    ui->lab_num->setText(num);
}

void OrderItem::setProprice(QString price){
    ui->lab_price->setText(price);
}

void OrderItem::setProtolprice(QString tolprice){
    ui->lab_tolprice->setText(tolprice);
}
