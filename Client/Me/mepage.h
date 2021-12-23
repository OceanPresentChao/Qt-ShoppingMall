#ifndef MEPAGE_H
#define MEPAGE_H

#include <QWidget>
#include"../shoppingclient.h"
#include"../person.h"
#include<QListWidget>
#include<QListWidgetItem>
#include "meitem.h"

namespace Ui {
class MePage;
}

class MePage : public QWidget
{
    Q_OBJECT

public:
    explicit MePage(QWidget *parent = nullptr);
    ~MePage();
    ShoppingClient *client;
    void addMeItem(QString key,QString val,QString pic_add="");
    QMap<QString,MeItem*>infolist;

private:
    Ui::MePage *ui;
    Person* someone;

private slots:
    void getSomeone(Person*);
    void updateUserMoney(int num);
};

#endif // MEPAGE_H
