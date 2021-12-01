#include "server.h"
#include "dialog.h"

Server::Server(QObject *parent)
{
    dialog = dynamic_cast<Dialog *>(parent);//找爸爸
    sqlserver = new SQLServer("QMYSQL","127.0.0.1",3306,"ShoppingMall","root","chb20020309");
    sqlserver->connectToDataBase();

    tcpserver = new TcpServer(parent);//tcpserver和会话窗口相连
    tcpserver->listen(QHostAddress::Any,520);
}
