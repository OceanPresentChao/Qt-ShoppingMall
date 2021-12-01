#include "sqlserver.h"

SQLServer::SQLServer()
{

}

SQLServer::SQLServer(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password){   
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        db = QSqlDatabase::addDatabase(SQLkind);
    }
    database_IP = ip;
    database_port = port;
    database_username = username;
    database_dbname = dbname;
    database_password = password;
}

bool SQLServer::connectToDataBase(){
    db.setHostName(database_IP);
    db.setPort(database_port);
    db.setDatabaseName(database_dbname);
    db.setUserName(database_username);
    db.setPassword(database_password);
    if(db.open()){
        query = new QSqlQuery(db);//query绑定
        qDebug()<<"连接数据库成功！";
        //emit signal_connectDatabase(true);
        return true;
    }
    else {
        qDebug()<<"连接数据库成功！";
        //emit signal_connectDatabase(false);
    }
    return false;
}

void SQLServer::test(){
    QSqlQuery query(db);
    query.exec("create table course (id int primary key, "
    "name varchar(20), teacher varchar(20))");
    query.exec("insert into course values(0, '数学', '刘老师')");
    query.exec("insert into course values(1, '英语', '张老师')");
    query.exec("insert into course values(2, '计算机', '李老师')");

}
