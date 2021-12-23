#ifndef REGISTERWGT_H
#define REGISTERWGT_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QMessageBox>
#include"shoppingclient.h"
#include<QJsonObject>
#include<QJsonArray>
namespace Ui {
class RegisterWgt;
}

class RegisterWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWgt(ShoppingClient*);
    ~RegisterWgt();


private:
    Ui::RegisterWgt *ui;
    void paintEvent(QPaintEvent *event);
    ShoppingClient *client;
private slots:
    void registerUser();
};

#endif // REGISTERWGT_H
