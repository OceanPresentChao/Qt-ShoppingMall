#ifndef CONTACTPAGE_H
#define CONTACTPAGE_H

#include <QWidget>
#include<QUdpSocket>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QJsonObject>
#include"shoppingmanager.h"
namespace Ui {
class ContactPage;
}

class ContactPage : public QWidget
{
    Q_OBJECT

public:
    explicit ContactPage(QWidget *parent = nullptr);
    ~ContactPage();
    ShoppingManager *manager;

private:
    Ui::ContactPage *ui;
    QUdpSocket *udpsocket;
    qintptr port;
    bool appendMsg(QJsonObject obj);
private slots:
    void receiveMessage();
    void sendMessage();
};

#endif // CONTACTPAGE_H
