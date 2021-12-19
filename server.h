#ifndef SERVER_H
#define SERVER_H
#include "sqlserver.h"
#include "tcpserver.h"
#include"handleserver.h"
#include<QObject>

class Server:public QObject
{
public:
    Server(QObject *parent);
    TcpServer *tcpserver;
    SQLServer *sqlserver;
    HandleServer *handleserver;

private:
    Dialog *dialog;//指向主窗口
};

#endif // SERVER_H
