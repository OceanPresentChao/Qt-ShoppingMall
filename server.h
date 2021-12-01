#ifndef SERVER_H
#define SERVER_H
#include "sqlserver.h"
#include "tcpserver.h"
class TcpServer;
class SQLServer;
class Server
{
public:
    Server(QObject *parent);
    TcpServer *tcpserver;
    SQLServer *sqlserver;

private:
    Dialog *dialog;//指向主窗口
};

#endif // SERVER_H
