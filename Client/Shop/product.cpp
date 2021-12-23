#include "product.h"

Product::Product()
{

}

Product::Product(QJsonObject obj){
    QString _name = obj.value("pro_name").toString();
    QString _id = obj.value("pro_id").toString();
    QString _price = obj.value("pro_price").toString();
    QString _amount = obj.value("pro_amount").toString();
    QString _sales = obj.value("pro_sales").toString();
    QString _classification = obj.value("pro_classification").toString();
    QString _about = obj.value("pro_about").toString();
    QString _istimelimited = obj.value("pro_istimelimited").toString().toLower();
    QString _pictureaddress = obj.value("pro_pictureaddress").toString();
    this->name = _name;
    this->id = _id.toInt();
    this->price = _price.toInt();
    this->amount = _amount.toInt();
    this->sales = _sales.toInt();
    this->classification = _classification;
    this->about = _about;
    this->pictureaddress = _pictureaddress;
    if(_istimelimited == "true"){this->islimited = true;}
    else{this->islimited = false;}
}
