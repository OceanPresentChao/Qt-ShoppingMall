#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

#include <QDebug>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(qintptr sockDesc, QObject *parent = Q_NULLPTR);
    ~MySocket();
    qintptr getPort();

signals:
    void socket_dataReady(const QString &ip, const qintptr,const QByteArray data);
    void signal_socket_disconnected(qintptr);

public slots:
    void socket_recvData(void);
    void socket_sendData(qintptr id, const QByteArray data);
    void socket_disConnected();

private:
    qintptr m_sockDesc;
};

#endif // MYSOCKET_H
