#include "mysocket.h"

MySocket::MySocket(qintptr sockDesc, QObject *parent) :
    QTcpSocket(parent),
    m_sockDesc(sockDesc)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(socket_recvData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(socket_disConnected()));
    //qDebug()<<QString("服务端socket端口：%1").arg(sockDesc);
}

MySocket::~MySocket()
{

}

void MySocket::socket_sendData(qintptr id, const QByteArray data)
{
    if (id == m_sockDesc) {
        this->write(data);
        qDebug()<<QString("socket已发送消息 端口:%1").arg(m_sockDesc);
    }
}

void MySocket::socket_recvData(void)
{
    QString ip = peerAddress().toString().remove(0, 7);
    qintptr port = m_sockDesc;
    QByteArray data = readAll();

    emit socket_dataReady(ip,port, data);//有消息来了
    qDebug()<<QString("服务端socket接受到消息 端口：%1").arg(m_sockDesc);
}

void MySocket::socket_disConnected(){
    //qDebug()<<"Mysocket断开连接";
    emit signal_socket_disconnected(m_sockDesc);
}

qintptr MySocket::getPort(){
    return m_sockDesc;
}
