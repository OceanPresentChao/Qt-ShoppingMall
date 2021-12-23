#include "mepage.h"
#include "ui_mepage.h"
#include<QtDebug>
MePage::MePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MePage)
{
    ui->setupUi(this);
    //ui->pushButton_people->
    ui->listWidget->setStyleSheet("QListWidget::Item{ background:white;height:80px;}QListWidget::Item:hover{background:rgb(246,246,247);}QListWidget{border:0;}");
}

MePage::~MePage()
{
    delete ui;
}

void MePage::getSomeone(Person* p){
    someone = p;
    qDebug()<<"getsomeone!";
    ui->lab_name->setText(someone->name);
    ui->widget_pic->setStyleSheet("border-image:url(:/images/products/4.png);border-radius:45px;");
    this->addMeItem("性别",someone->gender,"icon3.png");
    this->addMeItem("余额",QString::number(someone->getmoney()),"icon2.png");
    this->addMeItem("地址",someone->address,"icon1.png");
}

void MePage::addMeItem(QString key, QString val, QString pic_add){
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    MeItem *nitem = new MeItem();
    nitem->setKey(key);
    nitem->setVal(val);
    if(pic_add != ""){
        nitem->setPic(pic_add);
    }
    ui->listWidget->setItemWidget(item,nitem);
    this->infolist.insert(key,nitem);//将项目加入map中
}

void MePage::updateUserMoney(int num){
    MeItem *item = infolist.value("余额");
    item->setVal(QString::number(num));
}


