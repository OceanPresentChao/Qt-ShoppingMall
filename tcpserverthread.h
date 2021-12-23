#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QDebug>

#include "mysocket.h"

class MySocket;

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    TcpServerThread(qintptr sockDesc, QObject *parent = Q_NULLPTR);
    ~TcpServerThread();
    MySocket* getSocket();
    qintptr getPort();

private:
    void run(void);

public slots:
    void thread_sendData(qintptr sockDesc, const QByteArray data);

signals:
    void signal_thread_dataReady(const QString &ip,const qintptr, const QByteArray data);
    void signal_thread_sendData(qintptr sockDesc, const QByteArray data);
    void signal_thread_disconnect(qintptr sockDesc);

private slots:   
    void thread_recvData(const QString &ip,const qintptr, const QByteArray data);
    void thread_disconnectToHost(qintptr);

private:
    MySocket *m_socket;
    qintptr m_port;
};

#endif // SERVERTHREAD_H
