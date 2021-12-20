#ifndef HANDLESERVER_H
#define HANDLESERVER_H

#include <QObject>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonParseError>
#include"sqlserver.h"

class HandleServer:public QObject
{
    Q_OBJECT
public:
    HandleServer(SQLServer*);
    void jsonResReady(QString head,QJsonArray res,qintptr port,QString errmsg="");
    QString getRandomOrderNum();
private:
    SQLServer *sql;
    void handleLogin(QJsonObject body,qintptr port);
    void handleRegister(QJsonObject body,qintptr port);
    void handleSearchProduct(QJsonObject body,qintptr port);
    void handleAddCart(QJsonObject body,qintptr port);
    void handleDelCart(QJsonObject body,qintptr port);
    void handleUpdateCart(QJsonObject body,qintptr port);
    void handleSearchCart(QJsonObject body,qintptr port);
    void handleBuySth(QJsonObject body,qintptr port);
    bool createOrderItems(QJsonArray wannabuy,QJsonObject map,QString ordernum);
    void handleSearchOrder(QJsonObject body,qintptr port);
    void handleSearchOrderItems(QJsonObject body,qintptr port);

public slots:
    void handleRequest(const QString&,const qintptr, const QByteArray);
signals:
    void signal_responeReady(const QByteArray,qintptr);
};

#endif // HANDLESERVER_H
