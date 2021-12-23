#include "productitem.h"
#include "ui_productitem.h"
#include<QtDebug>

ProductItem::ProductItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductItem)
{
    ui->setupUi(this);
//    ui->lab_num->setFont()
    this->setStyleSheet("QLabel{background:transparent;}"
                        );
    ui->lab_name->setStyleSheet("QLabel{color:rgb(51,51,51);}");
    ui->lab_ranking->setStyleSheet("QLabel{color:rgb(204,204,204);}");
    ui->lab_message->setStyleSheet("QLabel{color:rgb(153,153,153);}");

}

ProductItem::~ProductItem()
{
    delete ui;
}

void ProductItem::setLabNumColor(bool bo)
{
    if(bo == false)
    {
        ui->lab_num->setStyleSheet("QLabel{color:rgb(255,61,61)}");
    }
    else {
        ui->lab_num->setStyleSheet("QLabel{color:rgb(222,222,222)}");
    }
}

void ProductItem::setLabNumText(QString str)
{
    ui->lab_num->setText(str);
}

void ProductItem::setLabNameText(QString str)
{
    ui->lab_name->setText(str);
}

void ProductItem::setLabrankingText(QString str)
{
    ui->lab_ranking->setText(str);
}

void ProductItem::setLabMessageText(QString str)
{
    ui->lab_message->setShowText(str);
}

void ProductItem::setId(QString id){
    int num = id.toInt();
    this->id = num;
    return;
}

void ProductItem::mouseDoubleClickEvent(QMouseEvent *event){
    emit signal_proitem_dblclick(id);
    return;
}

