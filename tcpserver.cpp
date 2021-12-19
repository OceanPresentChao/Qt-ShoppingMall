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
{
    qDebug()<<QString("新的连接：端口%1").arg(sockDesc);
    m_socketList.append(sockDesc);//放入新的端口号

    TcpServerThread *thread = new TcpServerThread(sockDesc);
    threadlist.append(thread);//把新的thread放入threadlist

    emit signal_newConnection(sockDesc);//告诉dialog有新的连接

    connect(thread, SIGNAL(signal_thread_disconnect(qintptr)), this, SLOT(clientDisconnected(qintptr)));
    connect(thread, SIGNAL(signal_thread_dataReady(const QString&, const qintptr,const QByteArray)),this,SLOT(recvData(const QString&,const qintptr, const QByteArray)));
    //connect(thread, SIGNAL(signal_thread_dataReady(const QString&, const QByteArray)), m_dialog, SLOT(dialog_recvData(const QString&, const QByteArray)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();//启动线程，将调用thread的run函数
}

void TcpServer::clientDisconnected(qintptr sockDesc)
{
    emit signal_disConnection(sockDesc);//告诉dialog有断开连接的
    foreach(TcpServerThread *item,threadlist){
        if(item->getPort() == sockDesc){
            threadlist.removeOne(item);//移除断开连接的thread
            item->quit();
            item->wait();
            delete item;
        }
    }
    m_socketList.removeOne(sockDesc);
    qDebug()<<QString("断开连接，端口：%1").arg(sockDesc);
}

void TcpServer::recvData(const QString& ip,const qintptr port, const QByteArray data){
    emit signal_recvData(ip,port,data);
}

void TcpServer::sendResponse(const QByteArray data,qintptr port){
    foreach(TcpServerThread *item,threadlist){
        if(item->getPort() == port){
            item->thread_sendData(port,data);
            //qDebug()<<QString("线程sendResponse 端口：%1").arg(port);
            return;
        }
    }
}
