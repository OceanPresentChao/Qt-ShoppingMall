#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H

#include <QWidget>
#include "product.h"
#include<QDesktopWidget>

namespace Ui {
class ProductPage;
}

class ProductPage : public QWidget
{
    Q_OBJECT

public:
    ProductPage(Product *pro,QWidget *parent = nullptr);
    ~ProductPage();
    Product *product;
    void initPage(Product*);

private:
    Ui::ProductPage *ui;
    QString pic_path;
signals:
    void signal_addToCart(Product*);
public slots:
    void addProductToCart();
};

#endif // PRODUCTPAGE_H
