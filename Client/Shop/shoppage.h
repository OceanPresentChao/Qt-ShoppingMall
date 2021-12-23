#ifndef SHOPPAGE_H
#define SHOPPAGE_H

#include <QWidget>
#include "../shoppingclient.h"
#include<QStackedWidget>
#include<QVector>
#include<QMap>
#include "product.h"
#include "productitem.h"
#include"productpage.h"
#include<QAction>
#include<QActionEvent>
#include<QRegularExpression>
#include<QMenu>
namespace Ui {
class ShopPage;
}

class ShopPage : public QWidget
{
    Q_OBJECT

public:
    explicit ShopPage(QWidget *parent = nullptr);
    ~ShopPage();
    ShoppingClient *client;
    void showEvent(QShowEvent *event);
    QMap<int,Product*> productlist;//用产品的主键作为标识

private:
    Ui::ShopPage *ui;
    QStackedWidget *m_stackedwidget;
    bool isCached;
    QVector<bool>stack_isCached;
    void initClassification();
    void contextMenuEvent(QContextMenuEvent *event);
public slots:
    void updateOneClass(int currow);
    void showProduct(int id);
    void addToCart(Product*);
    void searchProduct();
signals:
    void signal_addToCart(Product*);
    void signal_refresh(int);
};

#endif // SHOPPAGE_H
