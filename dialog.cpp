#include <QMessageBox>
#include<QString>
#include "tcpserver.h"
#include "dialog.h"
#include "ui_dialog.h"
#include<QJsonDocument>
#include<QJsonObject>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_count(0)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);

    connect(ui->btnClear,SIGNAL(clicked()),this, SLOT(clearData()));

    TotalServer = new Server(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showConnection(int sockDesc)
{
    m_count++;

    /* 在下托列表加一上新增的socket选项*/
    ui->comboBoxObj->addItem(QString("%1").arg(sockDesc), sockDesc);
    /* 修改socket总数 */
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::showDisconnection(int sockDesc)
{
    m_count--;
    //ui->comboBoxObj->clear();
    int index = ui->comboBoxObj->findData(sockDesc);
    ui->comboBoxObj->removeItem(index);
    ui->labelNum->setText(QString("%1").arg(m_count));

}

void Dialog::dialog_recvData(const QString &ip, const char *data)
{
    QString msg;
    QString content=data;
     msg += content + "\n";
    ui->textBrowser->append(msg);
}

void Dialog::clearData(void)
{
    ui->textBrowser->clear();
}
/*
void Dialog::test(){
    QJsonObject p;
    p.insert("name","chao");
    p.insert("age",19);
    QJsonDocument document;
    document.setObject(p);
    QByteArray arr = document.toJson();
}
*/
