#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

#include <QDebug>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(int sockDesc, QObject *parent = Q_NULLPTR);
    ~MySocket();

signals:
    void socket_dataReady(const QString &ip, const char *data);

public slots:
    void socket_recvData(void);
    void socket_sendData(int id, const char *data);

private:
    int m_sockDesc;
};

#endif // MYSOCKET_H
