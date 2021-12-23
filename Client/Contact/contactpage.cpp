#include "contactpage.h"
#include "ui_contactpage.h"

ContactPage::ContactPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactPage)
{
    ui->setupUi(this);
    port = 2227;
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(port,QUdpSocket::ShareAddress |QUdpSocket::ReuseAddressHint);
        connect(udpsocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMessage()));


}

ContactPage::~ContactPage()
{
    delete ui;
}


void ContactPage::receiveMessage(){
    QByteArray res;
    quint16 p;
    QHostAddress targetaddr;//ip
        while(udpsocket->hasPendingDatagrams())
        {
            res.resize(udpsocket->pendingDatagramSize());
            udpsocket->readDatagram(res.data(), res.size(),&targetaddr,&p);
            QJsonParseError jsonError;
            QJsonDocument doucment = QJsonDocument::fromJson(res, &jsonError);  // 转化为 JSON 文档
            if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
                if (doucment.isObject()) {  // JSON 文档为对象
                    QJsonObject object = doucment.object();  // 转化为对象
                    appendMsg(object);
                    }
                }
            }
         qDebug()<<"udpsocket receive!"<<res.size();
         qDebug()<<targetaddr<<p;
}

void ContactPage::sendMessage(){
    QJsonObject content;
    content.insert("msg",QJsonValue(ui->textEdit->toPlainText()));
    content.insert("name",QJsonValue(client->getPerson()->name));
    QJsonDocument document;
    document.setObject(content);
    QByteArray data = document.toJson();
    udpsocket->writeDatagram(data,data.size(),QHostAddress::LocalHost,227);
    qDebug()<<"发送成功！";
    ui->textEdit->clear();
}

bool ContactPage::appendMsg(QJsonObject obj){
    QString context = "";
    QString name = "";
    QString msg = "";
    if(obj.contains("name")){
        name = obj.value("name").toString();
    }
    if(obj.contains("msg")){
        msg = obj.value("msg").toString();
    }
    ui->textEdit_2->append(name+":");
    ui->textEdit_2->append(msg);
    return true;
}
