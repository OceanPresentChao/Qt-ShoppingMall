#include "tcpserverthread.h"
#include <QMetaType>
TcpServerThread::TcpServerThread(qintptr sockDesc, QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
    m_port = sockDesc;

}

TcpServerThread::~TcpServerThread()
{
    m_socket->close();
}

void TcpServerThread::run(void)
{
    m_socket = new MySocket(m_port);
    if (!m_socket->setSocketDescriptor(m_port)) {//原来这一步是必须的QAQ
        return ;
    }
    connect(m_socket, SIGNAL(signal_socket_disconnected(qintptr)), this, SLOT(thread_disconnectToHost(qintptr)));
    connect(m_socket, SIGNAL(socket_dataReady(const QString&,const qintptr, const QByteArray)),this, SLOT(thread_recvData(const QString&,const qintptr, const QByteArray)));//接受消息
    connect(this, SIGNAL(signal_thread_sendData(qintptr, const QByteArray)),m_socket, SLOT(socket_sendData(qintptr, const QByteArray)));

    this->exec();
}

void TcpServerThread::thread_sendData(qintptr sockDesc, const QByteArray data)
{
    emit signal_thread_sendData(sockDesc, data);
}

void TcpServerThread::thread_recvData(const QString &ip,const qintptr port, const QByteArray data)
{
    emit signal_thread_dataReady(ip,port,data);
}

void TcpServerThread::thread_disconnectToHost(qintptr port)
{
    emit signal_thread_disconnect(port);
    //qDebug()<<"线程断开连接";
}

MySocket* TcpServerThread::getSocket(){
    return m_socket;
}

qintptr TcpServerThread::getPort(){
    return m_port;
}
