#include "cartpage.h"
#include "ui_cartpage.h"
#include<QtDebug>
CartPage::CartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartPage)
{
    ui->setupUi(this);
    ui->list_item->setStyleSheet("QListWidget{border:1px;background:#EEE;border-radius:5px;}"//设置ui列表的样式表
                           "QListWidget::Item{ background:white;height:80px;}"
                           "QListWidget::Item:hover{background:rgb(246,246,247);}"
                           );
    this->tolprice = 0;
    ui->lab_tolprice->setText(QString("总价: $%1").arg(this->tolprice));
    isCached = false;
    connect(ui->btn_buy,SIGNAL(clicked()),this,SLOT(buySth()));
    connect(this,SIGNAL(signal_updateCartMoney(int)),this,SLOT(updateCartMoney(int)));
}

CartPage::~CartPage()
{
    delete ui;
}

void CartPage::loadCart(){
    QJsonObject obj;
    obj.insert("want","cartitems.cart_pro_id,pro_name,pro_price,pro_pictureaddress,cart_num,pro_price*cart_num AS cart_tolprice");
    obj.insert("restriction",QJsonValue(QString("products.pro_id = cartitems.cart_pro_id AND cart_user_id = %1").arg(client->getPerson()->getId())));
    QByteArray data = client->sendCHTTPMsg("10304",obj);//查询购物车
    QString flag = client->parseHead(data);
    if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
    else{
        QJsonArray res = client->parseResponse(data);
        //qDebug()<<res;
        for(int i = 0; i < res.size(); i++){
            QJsonObject p = res[i].toObject();
            int _id = p.value("cart_pro_id").toString().toInt();
            int _initnum = p.value("cart_num").toString().toInt();
            int _price = p.value("pro_price").toString().toInt();
            int _tolprice = p.value("cart_tolprice").toString().toInt();
            QString _name = p.value("pro_name").toString();
            QString _address = p.value("pro_pictureaddress").toString();
            QListWidgetItem *item = new QListWidgetItem(ui->list_item);
            CartItem * nitem = new CartItem(_id,_address,_name,_price,_tolprice,_initnum);
            nitem->widgetitem = item;
            connect(nitem,SIGNAL(signal_checkedchanged(int)),this,SLOT(addChange(int)));
            connect(nitem,SIGNAL(signal_valchanged(int,int)),this,SLOT(updateCart(int,int)));
            connect(nitem,SIGNAL(signal_delItem(int)),this,SLOT(deleteCart(int)));
            ui->list_item->setItemWidget(item,nitem);
            cartlist.insert(_id,nitem);
        }
    }
}

void CartPage::showEvent(QShowEvent *event){
    if(!isCached){
    loadCart();
    isCached = true;
    }
    return QWidget::showEvent(event);
}

void CartPage::addToCart(Product* product){
    if(!isCached){loadCart();isCached = true;}
    QJsonObject obj;
    obj.insert("cart_pro_id",QJsonValue(QString::number(product->id)));
    obj.insert("cart_user_id",QJsonValue(QString::number(client->getPerson()->getId())));
    if(!cartlist.contains(product->id)){
        obj.insert("cart_num",QJsonValue(QString::number(1)));
        QByteArray data = client->sendCHTTPMsg("10301",obj);//加入购物车
        QString flag = client->parseHead(data);
        if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
        else{QMessageBox::information(nullptr,"通知","加入成功！");}
        QListWidgetItem *item = new QListWidgetItem(ui->list_item);
        CartItem * nitem = new CartItem(product->id,product->pictureaddress,product->name,product->price,product->price,1);
        nitem->widgetitem = item;
        connect(nitem,SIGNAL(signal_checkedchanged(int)),this,SLOT(addChange(int)));//ui界面上价格改变
        connect(nitem,SIGNAL(signal_valchanged(int,int)),this,SLOT(updateCart(int,int)));//spinbox数量改变
        connect(nitem,SIGNAL(signal_delItem(int)),this,SLOT(deleteCart(int)));
        ui->list_item->setItemWidget(item,nitem);
        cartlist.insert(product->id,nitem);
    }
    else{
        CartItem *p = cartlist.value(product->id);
        p->setSpinNum(p->getSpinNum()+1);
    }
}

void CartPage::updateCart(int pro_id,int num){//通过购物车item对应的商品id查找
    QJsonObject obj;
    obj.insert("cart_pro_id",QJsonValue(QString::number(pro_id)));
    obj.insert("cart_user_id",QJsonValue(QString::number(client->getPerson()->getId())));
    obj.insert("cart_num",QJsonValue(QString::number(num)));
    obj.insert("restriction",QJsonValue(QString("cart_user_id = '%1' AND cart_pro_id = '%2'").arg(client->getPerson()->getId()).arg(pro_id)));
    QByteArray data = client->sendCHTTPMsg("10303",obj);//修改购物车
    QString flag = client->parseHead(data);
    if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
}

void CartPage::deleteCart(int pro_id){

    QJsonObject obj;
    obj.insert("restriction",QJsonValue(QString("cart_user_id = '%1' AND cart_pro_id = '%2'").arg(client->getPerson()->getId()).arg(pro_id)));
    QByteArray data = client->sendCHTTPMsg("10302",obj);//删除购物车项
    QString flag = client->parseHead(data);
    if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
    QListWidgetItem* item = ui->list_item->currentItem();//被选中或背点击的item删除
//    QListWidgetItem* item = ui->listWidget->takeItem(2);//指定删除
    ui->list_item->removeItemWidget(item);
    delete item;
    cartlist.remove(pro_id);
}

void CartPage::addChange(int change){
    this->tolprice += change;//购物车的总价
    ui->lab_tolprice->setText(QString("总价: $%1").arg(this->tolprice));
}

void CartPage::buySth(){
    QString dlgTitle="Question消息框";
    QString strInfo="是否确定结算？";
    QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
    QMessageBox::StandardButton result;//返回选择的按钮
    result=QMessageBox::question(this, dlgTitle, strInfo,QMessageBox::Yes|QMessageBox::Cancel,defaultBtn);
    if(result==QMessageBox::Yes){
       QString FLAG_INSKIND = "02";//商品操作属于02类
       QString FLAG_INS = "05";//执行的是购买操作
       QJsonObject obj;
       QJsonArray wannabuy;
       for(int i = 0;i < cartlist.keys().size(); i++){
           int _id = cartlist.keys().at(i);
           bool _ischecked = cartlist.value(_id)->getChecked();
           //qDebug()<<"移除前:"<<_id<<_ischecked;
           if(_ischecked){
               wannabuy.push_back(QJsonValue(QString::number(_id)));//如果购物车内该物品被选中就把它加入要购买的名单里
           }
       }
       //qDebug()<<wannabuy<<wannabuy.size();
       if(wannabuy.isEmpty()){QMessageBox::information(nullptr,"通知","您还未选择要购买的商品！");return;}//若没有商品被选中
       obj.insert("type",QJsonValue(QString("cart")));
       obj.insert("user_id",QJsonValue(QString::number(client->getPerson()->getId())));
       obj.insert("wannabuy",QJsonValue(wannabuy));
       QByteArray data = client->sendCHTTPMsg(FLAG_CHARACTER+FLAG_INSKIND+FLAG_INS,obj);
       QString flag = client->parseHead(data);
       if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
       else{
           QJsonArray response = client->parseResponse(data);
           emit signal_updateUserMoney(response[0].toInt());
           emit signal_updateCartMoney(response[1].toInt());
           QMessageBox::information(nullptr,"通知","购买成功！");
           for(int i = 0;i < wannabuy.size(); i++){
               int _id = wannabuy[i].toString().toInt();
               bool _ischecked = cartlist.value(_id)->getChecked();
               //qDebug()<<"移除后:"<<_id<<_ischecked;
               if(_ischecked){
                   ui->list_item->removeItemWidget(cartlist.value(_id)->widgetitem);//如果购物车内物品买完后清除
                   delete cartlist.value(_id)->widgetitem;
                   cartlist.remove(_id);//购物车表要移除
               }
           }
       }
    }
}

void CartPage::updateCartMoney(int change){
    this->tolprice -=change;
    ui->lab_tolprice->setText(QString("总价: $%1").arg(this->tolprice));
}
