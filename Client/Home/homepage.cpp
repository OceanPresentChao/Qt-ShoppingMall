#include "homepage.h"
#include "ui_homepage.h"
#include<QJsonDocument>
#include<QJsonObject>

HomePage::HomePage(ShoppingClient *parent) :
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    CarouselImageWindow *p = new CarouselImageWindow();//添加轮播图
    p->addImage(":/images/picturewall/1.png");
    p->addImage(":/images/picturewall/2.png");
    p->addImage(":/images/picturewall/3.png");
    p->addImage(":/images/picturewall/4.png");
    p->addImage(":/images/picturewall/5.png");
    p->addImage(":/images/picturewall/6.png");
    p->startPlay();
    ui->lunboLayout->addWidget(p);
}

HomePage::~HomePage()
{
    delete ui;
}
