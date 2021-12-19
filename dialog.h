#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"

namespace Ui {
class Dialog;
}

class Server;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = Q_NULLPTR);
    ~Dialog();
    Server *TotalServer;

private:
    Ui::Dialog *ui;
    int m_count;

private slots:
    friend class TcpServer;
    void showConnection(qintptr sockDesc);
    void showDisconnection(qintptr sockDesc);
    void clearData(void);
    void showRecv(const QString&,const qintptr,const QByteArray);
    void showSend(const QByteArray,qintptr);

};

#endif // DIALOG_H
