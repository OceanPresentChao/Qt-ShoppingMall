#ifndef SHOPPINGMANAGER_H
#define SHOPPINGMANAGER_H

#include <QWidget>
#include "slidenavigation.h"
#include <QSqlDatabase>
#include <QSqlQuery>
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
namespace Ui {
class ShoppingManager;
}

class ShoppingManager : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingManager(QWidget *parent = nullptr);
    ~ShoppingManager();
    QSqlDatabase getDataBase();
    QByteArray sendCHTTPMsg(QString CHTTP,QJsonObject jsonobj);
    QJsonArray parseResponse(QByteArray data);
    QString parseHead(QByteArray data);
    void error(QChar character,QString errmsg);
    Person* getPerson();
    bool getConnected();
    bool connectTo();
    bool disConnect();
    void loadStyleSheet(const QString &styleSheetFile);

public slots:
    void changePage(qintptr index);
    void someoneLogin(QJsonObject obj);
    void changeStyle(int index);

private:
    Ui::ShoppingManager *ui;
    void helpConnect();
    QSqlDatabase db;
    QTcpSocket *m_socket;
    QString server_IP;//服务端IP地址
    qintptr server_port;//服务端端口
    Person *logined_user;
    bool isconnected;
    void setServerIP(QString ip);
    void setServerPort(qintptr port);
    void closeEvent(QCloseEvent *event);
    bool connectToDataBase(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password);
};

#endif // SHOPPINGMANAGER_H
