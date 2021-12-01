#include "mysocket.h"

MySocket::MySocket(int sockDesc, QObject *parent) :
    QTcpSocket(parent),
    m_sockDesc(sockDesc)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(socket_recvData()));
}

MySocket::~MySocket()
{

}

void MySocket::socket_sendData(int id, const char *data)
{
    if (id == m_sockDesc && data!=NULL) {
        this->write(data,strlen(data));
    }
}

void MySocket::socket_recvData(void)
{
    QString ip = peerAddress().toString().remove(0, 7);
    char data[1024]={0};
    read(data,1024);

    emit socket_dataReady(ip, data);
}
