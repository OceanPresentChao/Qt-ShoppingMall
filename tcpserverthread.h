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
    TcpServerThread(int sockDesc, QObject *parent = Q_NULLPTR);
    ~TcpServerThread();
    int getSocketDesc();
    MySocket* getSocket();

private:
    void run(void);

public slots:
    void thread_sendDataSlot(int sockDesc, const char *data);

signals:
    void thread_dataReady(const QString &ip, const char *data);
    void thread_sendData(int sockDesc, const char *data);
    void disconnectTCP(int sockDesc);

private slots:   
    void thread_recvDataSlot(const QString &ip, const char *data);
    void disconnectToHost(void);

private:
    MySocket *m_socket;
    int m_sockDesc;
};

#endif // SERVERTHREAD_H
