#ifndef SHOPPINGCLIENT_H
#define SHOPPINGCLIENT_H

#include <QWidget>
#include "slidenavigation.h"
#include <QTcpSocket>
#include <QUdpSocket>
#include<QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QMouseEvent>
#include <QPainter>
#include<QJsonParseError>
#include"person.h"
extern QString FLAG_CHARACTER;
extern QString PIC_PATH;
namespace Ui {
class ShoppingClient;
}

class ShoppingClient : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingClient(QWidget *parent = nullptr);
    ~ShoppingClient();
    void setServerIP(QString ip);
    void setServerPort(qintptr port);
    bool connectTo();
    bool disConnect();
    QTcpSocket *m_socket;
    void closeEvent(QCloseEvent *event);
    QByteArray sendCHTTPMsg(QString CHTTP,QJsonObject jsonobj);
    QJsonArray parseResponse(QByteArray data);
    QString parseHead(QByteArray data);
    void error(QChar character,QString errmsg);
    bool getConnected();

    Person* getPerson();

private:
    Ui::ShoppingClient *ui;
    void helpConnect();//连接信号
    QString server_IP;//服务端IP地址
    qintptr server_port;//服务端端口
    Person *logined_user;
    bool isconnected;

public slots:
    void changePage(qintptr index);
private slots:
    void someoneLogin(QJsonObject);
signals:
    void signal_someonelogin(Person*);
};

#endif // SHOPPINGCLIENT_H
