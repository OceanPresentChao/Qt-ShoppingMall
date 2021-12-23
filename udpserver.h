#ifndef UDPSERVER_H
#define UDPSERVER_H
#include<QUdpSocket>
#include<QObject>
class UdpServer:public QObject
{
    Q_OBJECT
public:
    UdpServer();
private:
    qintptr port;
    QUdpSocket *udpsocket;
private slots:
    void receiveMessage();
};

#endif // UDPSERVER_H
