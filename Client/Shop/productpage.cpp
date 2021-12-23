#include "productpage.h"
#include "ui_productpage.h"
#include<QtDebug>
ProductPage::ProductPage(Product *pro,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductPage)
{
    ui->setupUi(this);
    pic_path = ":/images/products/";
    this->product = pro;
    initPage(this->product);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/4);
    connect(ui->btn_cart,SIGNAL(clicked()),this,SLOT(addProductToCart()));
}

ProductPage::~ProductPage()
{
    delete ui;
}

void ProductPage::initPage(Product *product){
    this->setWindowTitle("商品: "+product->name);
    ui->lab_about->setText("详细:"+product->about);
    ui->lab_name->setText(product->name);
    ui->lab_price->setText("$ "+QString::number(product->price));
    ui->lab_sales->setText("销量: "+QString::number(product->sales));
    ui->lab_amount->setText("剩余: "+QString::number(product->amount));
    QString pic_add = pic_path+product->pictureaddress;
    qDebug()<<pic_add;
    QPixmap pixmap(pic_add);
    if(pixmap.isNull()){
        pixmap.load(pic_path+"picerror.jpg");
    }
    ui->lab_pic->setPixmap(pixmap);
    pixmap.scaled(ui->lab_pic->size(), Qt::KeepAspectRatio);
    ui->lab_pic->setScaledContents(true);
    return;
}

void ProductPage::addProductToCart(){
    emit signal_addToCart(product);
    return;
}


