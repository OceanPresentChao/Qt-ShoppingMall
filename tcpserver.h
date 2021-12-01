#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

#include "tcpserverthread.h"

class Dialog;

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = Q_NULLPTR);
    ~TcpServer();
    QList<TcpServerThread*> threadlist;

private:
    void incomingConnection(qintptr sockDesc);

private slots:
    void clientDisconnected(int sockDesc);

private:
    Dialog *m_dialog;
    QList<int> m_socketList;//用来保存端口号
};

#endif // SERVER_H
