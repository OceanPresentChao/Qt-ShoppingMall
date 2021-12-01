#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"

namespace Ui {
class Dialog;
}

class TcpServer;
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

public slots:
    void dialog_recvData(const QString &ip, const char *data);

private slots:
    friend class TcpServer;
    void showConnection(int sockDesc);
    void showDisconnection(int sockDesc);
    void clearData(void);


};

#endif // DIALOG_H
