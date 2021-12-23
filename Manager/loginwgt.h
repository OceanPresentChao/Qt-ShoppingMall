#ifndef LOGINWGT_H
#define LOGINWGT_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QMessageBox>
#include<QRegExp>
#include<QRegExpValidator>
#include"shoppingmanager.h"
#include<QJsonObject>
#include<QJsonArray>
#include<QKeyEvent>
namespace Ui {
class LoginWgt;
}

class LoginWgt : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWgt(ShoppingManager *p);
    ~LoginWgt();
    ShoppingManager *client;

private:
    Ui::LoginWgt *ui;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
private slots:
    void loginUser();
signals:
    void signal_login(QJsonObject);
};

#endif // LOGINWGT_H
