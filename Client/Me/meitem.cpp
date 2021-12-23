#include "meitem.h"
#include "ui_meitem.h"

MeItem::MeItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeItem)
{
    ui->setupUi(this);

}

MeItem::~MeItem()
{
    delete ui;
}

void MeItem::setKey(QString str){
    ui->lab_key->setText(str);
}

void MeItem::setVal(int num){
    ui->lab_val->setNum(num);
}

void MeItem::setVal(QString str){
    ui->lab_val->setText(str);
}

void MeItem::setPic(QString picadd){
    QString add = ":/images/icons/";
    QPixmap pixmap(add+picadd);
    if(pixmap.isNull()){
        add += "picerror.png";
    }
    else{
        add += picadd;
    }
   QString str = "QWidget{border-image:url("+add+");}";
   ui->widget->setStyleSheet(str);

}
