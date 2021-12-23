#include "orderpage.h"
#include "ui_orderpage.h"

OrderPage::OrderPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderPage)
{
    ui->setupUi(this);
    ui->listWidget->setStyleSheet("QListWidget{border:1px;background:#EEE;border-radius:5px;}"//设置ui列表的样式表
                           "QListWidget::Item{ background:white;height:80px;}"
                           "QListWidget::Item:hover{background:rgb(246,246,247);}"
                           );
    this->current = 0;
    connect(ui->btn_back,SIGNAL(clicked()),this,SLOT(backOrder()));
    connect(ui->btn_next,SIGNAL(clicked()),this,SLOT(nextOrder()));
}

OrderPage::~OrderPage()
{
    delete ui;
}

void OrderPage::showEvent(QShowEvent *event){
    getAllOrder();
    qDebug()<<"order num:"<<orderlist.size();
}

void OrderPage::getAllOrder(){
    orderlist.clear();
    QString FLAG_INSKIND = "04";//订单操作属于04类
    QString FLAG_INS = "04";//执行的是查询操作
    QJsonObject obj;
    obj.insert("want",QJsonValue(QString("*")));
    obj.insert("restriction",QJsonValue(QString("order_user_id= %1").arg(client->getPerson()->getId())));
    QByteArray data = client->sendCHTTPMsg(FLAG_CHARACTER+FLAG_INSKIND+FLAG_INS,obj);
    QString flag = client->parseHead(data);
    if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
    QJsonArray result = client->parseResponse(data);
    if(!result.isEmpty()){
    for(int i = 0;i < result.size(); i++){
        QJsonObject obj = result[i].toObject();
        QString key = obj.value("order_id").toString();
        orderlist.insert(key,obj);
    }
    updateOrderItems(orderlist.value(orderlist.keys().at(0)).value("order_id").toString());
    }
}

void OrderPage::updateOrderItems(QString ordernum){
    qDebug()<<ordernum;
    QString FLAG_INSKIND = "04";//订单操作属于04类
    QString FLAG_INS = "05";//执行的是特殊查询操作
    QJsonObject obj;
    obj.insert("want","pro_pictureaddress,pro_name,orderitem_num,orderitem_pro_price,orderitem_num*orderitem_pro_price AS orderitem_tolprice");
    obj.insert("restriction",QString("products.pro_id = orderitems.orderitem_pro_id AND orderitems.orderitem_order_id = orders.order_id AND orderitem_order_id = '%1'").arg(ordernum));
    QByteArray data = client->sendCHTTPMsg(FLAG_CHARACTER+FLAG_INSKIND+FLAG_INS,obj);
    QString flag = client->parseHead(data);
    if(flag[0] != "1"){client->error(flag[0],flag.mid(1));return;}
    ui->listWidget->clear();
    QJsonArray result = client->parseResponse(data);
    qDebug()<<"orderitems:"<<result.size();
    for(int i = 0;i < result.size(); i++){
        QJsonObject order = result[i].toObject();
        OrderItem *newitem = new OrderItem(order);
        addItem(newitem);
    }
    QJsonObject order = orderlist.value(ordernum);
    ui->lab_status->setText(order.value("order_status").toString());
    ui->lab_price->setText(order.value("order_tolprice").toString());
    ui->lab_time->setText(order.value("order_time").toString());
    ui->lab_order->setText(ordernum);
}

void OrderPage::addItem(OrderItem *item){
    QListWidgetItem *newWidget = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(newWidget,item);
}

void OrderPage::backOrder(){
    current = (current+orderlist.size()-1)%orderlist.size();
    QString num = orderlist.value(orderlist.keys().at(current)).value("order_id").toString();
    updateOrderItems(num);
}

void OrderPage::nextOrder(){
    current = (current+orderlist.size()+1)%orderlist.size();
    QString num = orderlist.value(orderlist.keys().at(current)).value("order_id").toString();
    updateOrderItems(num);
}
