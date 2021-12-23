#include "server.h"
#include "dialog.h"

Server::Server(QObject *parent):QObject(parent)
{
    dialog = dynamic_cast<Dialog *>(parent);//找爸爸
    sqlserver = new SQLServer("QMYSQL","127.0.0.1",3306,"ShoppingMall","root","chb20020309");
    sqlserver->connectToDataBase();

    tcpserver = new TcpServer(parent);//tcpserver和会话窗口相连
    tcpserver->listen(QHostAddress::Any,520);

    handleserver = new HandleServer(sqlserver);

    udpserver = new UdpServer();

    connect(tcpserver,SIGNAL(signal_recvData(const QString&,const qintptr,const QByteArray)),handleserver,SLOT(handleRequest(const QString&,const qintptr, const QByteArray)));
    connect(handleserver,SIGNAL(signal_responeReady(const QByteArray,qintptr)),tcpserver,SLOT(sendResponse(const QByteArray ,qintptr)));

    connect(tcpserver,SIGNAL(signal_recvData(const QString&,const qintptr,const QByteArray)),dialog,SLOT(showRecv(const QString&,const qintptr,const QByteArray)));
    connect(handleserver,SIGNAL(signal_responeReady(const QByteArray,qintptr)),dialog,SLOT(showSend(const QByteArray,qintptr)));
}
