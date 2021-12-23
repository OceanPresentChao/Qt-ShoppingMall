#include <QMessageBox>
#include<QString>
#include "tcpserver.h"
#include "dialog.h"
#include "ui_dialog.h"
#include<QJsonDocument>
#include<QJsonObject>
#include<QDateTime>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_count(0)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);

    TotalServer = new Server(this);
    connect(ui->btnClear,SIGNAL(clicked()),this, SLOT(clearData()));
    connect(TotalServer->tcpserver,SIGNAL(signal_newConnection(qintptr)),this,SLOT(showConnection(qintptr)));
    connect(TotalServer->tcpserver,SIGNAL(signal_disConnection(qintptr)),this,SLOT(showDisconnection(qintptr)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showConnection(qintptr sockDesc)
{
    m_count++;

    /* 在下托列表加一上新增的socket选项*/
    ui->comboBoxObj->addItem(QString("%1").arg(sockDesc), sockDesc);
    /* 修改socket总数 */
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::showDisconnection(qintptr sockDesc)
{
    m_count--;
    //ui->comboBoxObj->clear();
    int index = ui->comboBoxObj->findData(int(sockDesc));
    ui->comboBoxObj->removeItem(index);
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::clearData(void)
{
    ui->textBrowser->clear();
}

void Dialog::showRecv(const QString& ip,const qintptr port,const QByteArray data){
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString time = "时间:" + curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject obj = document.object();
    QString head = obj.value("head").toString();
    QString content = QString(time + "\n" + "端口:%1->服务器: 报文头部:" + head + "\n").arg(port);
    ui->textBrowser->append(content);
}

void Dialog::showSend(const QByteArray data,qintptr port){
    QDateTime curDateTime=QDateTime::currentDateTime();
    QString time = "时间:" + curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject obj = document.object();
    QString head = obj.value("head").toString();
    QString content = QString(time + "\n" + "服务器->端口:%1 报文头部:" + head + "\n").arg(port);
    ui->textBrowser->append(content);
}
