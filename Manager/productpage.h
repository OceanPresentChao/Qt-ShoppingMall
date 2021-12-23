#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include"shoppingmanager.h"
#include<QMessageBox>
#include<QSqlError>
#include<QSqlRelationalDelegate>
namespace Ui {
class ProductPage;
}

class ProductPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProductPage(QWidget *parent = nullptr);
    ~ProductPage();
    ShoppingManager *manager;
    void showEvent(QShowEvent *event);

private:
    Ui::ProductPage *ui;
    QSqlTableModel *model;
    bool isCached;
private slots:
    void submitChange();
    void backChange();
    void searchProduct();
    void addProduct();
    void delProduct();
};

#endif // PRODUCTPAGE_H
