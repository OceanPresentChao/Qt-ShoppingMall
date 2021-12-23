#include "udpserver.h"

UdpServer::UdpServer()
{
    qDebug()<<"UDP!";
    port = 227;
    udpsocket = new QUdpSocket();//
    bool flag = udpsocket->bind(QHostAddress::LocalHost,port,QUdpSocket::ShareAddress |QUdpSocket::ReuseAddressHint);
    if(flag){
        connect(udpsocket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    }
}

void UdpServer::receiveMessage(){
    QByteArray res;
    quint16 p;
    QHostAddress targetaddr;//ip
        while(udpsocket->hasPendingDatagrams())
        {
            res.resize(udpsocket->pendingDatagramSize());
            udpsocket->readDatagram(res.data(), res.size(),&targetaddr,&p);
            qDebug()<<"udpsocket receive!"<<QString(res);
            udpsocket->writeDatagram(res,QHostAddress::Broadcast,p);
        }
}
