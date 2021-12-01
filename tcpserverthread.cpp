#include "tcpserverthread.h"

TcpServerThread::TcpServerThread(int sockDesc, QObject *parent) :
    QThread(parent),
    m_sockDesc(sockDesc)
{

}

TcpServerThread::~TcpServerThread()
{
    m_socket->close();
}

void TcpServerThread::run(void)
{
    m_socket = new MySocket(m_sockDesc);

    if (!m_socket->setSocketDescriptor(m_sockDesc)) {
        return ;
    }

    connect(m_socket, &MySocket::disconnected, this, &TcpServerThread::disconnectToHost);
    connect(m_socket, SIGNAL(socket_dataReady(const QString&, const char*)),this, SLOT(thread_recvDataSlot(const QString&, const char*)));
    connect(this, SIGNAL(thread_sendData(int, const char*)),m_socket, SLOT(socket_sendData(int, const char*)));

    this->exec();
}

void TcpServerThread::thread_sendDataSlot(int sockDesc, const char *data)
{
    if (data==NULL) {
        return ;
    }

    emit thread_sendData(sockDesc, data);
}

void TcpServerThread::thread_recvDataSlot(const QString &ip, const char *data)
{
    emit thread_dataReady(ip, data);
}

void TcpServerThread::disconnectToHost(void)
{
    emit disconnectTCP(m_sockDesc);
    m_socket->disconnectFromHost();
    this->quit();
}

int TcpServerThread::getSocketDesc(){
    return m_sockDesc;
}

MySocket* TcpServerThread::getSocket(){
    return m_socket;
}
