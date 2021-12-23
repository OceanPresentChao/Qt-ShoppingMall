#include "cartitem.h"
#include "ui_cartitem.h"
#include<QtDebug>
CartItem::CartItem(int pro_id,QString pro_address,QString pro_name,int pro_price,int tolprice,int initnum) :
    ui(new Ui::CartItem)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{background:transparent; border-radius:8px;}"
                        "QWidget:hover{background:transparent;}");

    ui->ProName->setText(pro_name);
    this->pro_id = pro_id;
    this->price = pro_price;
    this->num = initnum;
    this->setSpinNum(initnum);
    this->setPicture(pro_address);
    this->tolprice = tolprice;
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(valChanged(int)));
    connect(ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(setChecked()));
    ui->ProTolPrice->setText("总价:$"+QString::number(this->tolprice));
    ui->ProPrice->setText("单价:$"+QString::number(this->price));

    //这段代码不要乱改顺序！
}

CartItem::~CartItem()
{
    delete ui;
}


void CartItem::setPicture(QString url)
{
    QString add = ":/images/products/";
    QPixmap pixmap(add+url);
    if(pixmap.isNull()){
        add += "picerror.jpg";
    }
    else{
        add += url;
    }
   QString str = "QWidget{border-image:url("+add+");}";
   ui->widMusicPic->setStyleSheet(str);
}


void CartItem::setSpinNum(int num){
    ui->spinBox->setValue(num);
    this->num = num;
}

void CartItem::refreshMax(int maxnum){
    ui->spinBox->setMaximum(maxnum);
}

int CartItem::getSpinNum(){
    return ui->spinBox->value();
}

int CartItem::getProId(){
    return this->pro_id;
}

int CartItem::getprice(){
    return this->price;
}

bool CartItem::getChecked(){
    return ui->radioButton->isChecked();
}

void CartItem::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        bool flag = ui->radioButton->isChecked() == true ? false : true;
        ui->radioButton->setChecked(flag);
    }
}

void CartItem::contextMenuEvent(QContextMenuEvent *event)
{
        QAction *actionDel = new QAction(tr("删除"),this);
        this->addAction(actionDel);
        QMenu contextMenu;
        contextMenu.addAction(actionDel);
        QAction *selectedAction = contextMenu.exec(QCursor::pos());
        if(selectedAction == actionDel){
            emit signal_delItem(this->pro_id);
            qDebug()<<"contextMenu!Del!";
        }

}

void CartItem::setChecked(){
    bool flag = ui->radioButton->isChecked();
    //qDebug()<<this->getProId()<<flag;
    if(flag){
        emit signal_checkedchanged(tolprice);
    }
    else{
        emit signal_checkedchanged(-tolprice);
    }
}

void CartItem::valChanged(int num){
    this->num = num;
    int old_tolprice = this->tolprice;
    this->tolprice = num * this->price;
    int change = this->tolprice - old_tolprice;
    if(ui->radioButton->isChecked()){emit signal_checkedchanged(change);}//告诉页面有多少差价
    ui->ProTolPrice->setText("总价:$"+QString::number(this->tolprice));
    emit signal_valchanged(this->pro_id,num);
}
