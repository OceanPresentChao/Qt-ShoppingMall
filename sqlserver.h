#ifndef SQLSERVER_H
#define SQLSERVER_H
#include <QtSql>
#include <qmessagebox.h>
#include<QObject>
class SQLServer:public QObject
{

public:
    SQLServer();
    SQLServer(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password);
    QSqlDatabase db;
    QSqlQuery *query;
    bool connectToDataBase();
    void test();


private:
    QString database_IP;//数据库IP
    int database_port;//数据库端口号
    QString database_username;//数据库用户名
    QString database_password;//数据库密码
    QString database_dbname;//数据库名字

signals:
    void signal_connectDatabase(bool flag);
};

#endif // SQLSERVER_H
