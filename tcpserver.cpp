#include "dialog.h"
#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    m_dialog = dynamic_cast<Dialog *>(parent);//找爸爸
}

TcpServer::~TcpServer()
{

}

void TcpServer::incomingConnection(qintptr sockDesc)
{   qDebug()<<"端口"+sockDesc;
    m_socketList.append(sockDesc);

    TcpServerThread *thread = new TcpServerThread(sockDesc);
    threadlist.append(thread);//把新的thread放入threadlist

    m_dialog->showConnection(sockDesc);

    connect(thread, SIGNAL(disconnectTCP(int)), this, SLOT(clientDisconnected(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(thread_dataReady(const QString&, const char*)), m_dialog, SLOT(dialog_recvData(const QString&, const char*)));

    thread->start();
}

void TcpServer::clientDisconnected(int sockDesc)
{
    m_dialog->showDisconnection(sockDesc); 
    foreach(TcpServerThread *item,threadlist){
        if(item->getSocketDesc() == sockDesc){
            threadlist.removeOne(item);//移除断开连接的thread
            free(item);
        }
    }
}
