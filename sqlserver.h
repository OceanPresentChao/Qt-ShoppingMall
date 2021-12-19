#ifndef SQLSERVER_H
#define SQLSERVER_H
#include <QtSql>
#include<QVariantMap>
#include<QMap>
#include<QList>

class SQLServer:public QObject
{
    Q_OBJECT

public:
    SQLServer();
    SQLServer(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password,QObject *parent = Q_NULLPTR);
    bool connectToDataBase();
    QList<QString> getTableInfo(QString table);//获取表头
    bool selectSth(QString table,QJsonObject obj,QJsonArray &result);
    bool insertSth(QString table,QJsonObject obj);
    bool updateSth(QString table,QJsonObject obj);
    bool deleteSth(QString table,QJsonObject obj);

private:
    QSqlDatabase db;
    QString database_IP;//数据库IP
    int database_port;//数据库端口号
    QString database_username;//数据库用户名
    QString database_password;//数据库密码
    QString database_dbname;//数据库名字

    QJsonArray getSQLRes(QSqlQuery *q);//用query执行SQL语句将结果返回为json数组


signals:
    void signal_connectDatabase(bool flag);

};

#endif // SQLSERVER_H
