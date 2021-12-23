#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include"shoppingmanager.h"
#include<QMessageBox>
#include<QSqlRelationalTableModel>
#include<QSqlError>
#include<QSqlRelationalDelegate>
namespace Ui {
class OrderPage;
}

class OrderPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);
    ~OrderPage();
    ShoppingManager *manager;
    void showEvent(QShowEvent *event);

private:
    Ui::OrderPage *ui;
    QSqlRelationalTableModel *model;
    bool isCached;
private slots:
    void submitChange();
    void backChange();
    void searchOrder();
    void refreshOrder();
};

#endif // ORDERPAGE_H
