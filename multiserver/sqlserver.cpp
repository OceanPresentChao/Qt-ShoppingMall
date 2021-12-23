#include "sqlserver.h"
#include<QMessageBox>
SQLServer::SQLServer()
{

}

SQLServer::SQLServer(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password,QObject *parent):QObject (parent){
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
        qDebug()<<"连接数据库成功！";
        //emit signal_connectDatabase(true);
        return true;
    }
    else {
        qDebug()<<"连接数据库失败！";

        //emit signal_connectDatabase(false);
    }
    return false;
}

QJsonArray SQLServer::getSQLRes(QSqlQuery *q){
    QJsonArray res;
    //执行完exec函数后先next一次才是第一个数据
    while(q->next())
       {
          QJsonObject obj;
          //获取query所指向的记录在结果集中的编号
          //int rowNum = query->at();
          //获取每条记录中属性（即列）的个数
          int columnNum = q->record().count();
          //record.fieldName:键名
          //query.value 一行某列的值
          for(int i = 0;i < columnNum; i++){
              //query.value为varient类型，统一转换成字符串
              obj.insert(q->record().fieldName(i),QJsonValue(q->value(i).toString()));
              //qDebug()<<query->record().fieldName(i)+":"+query->value(i).toString();
          }
          res.append(QJsonValue(obj));//将一个对象值放入结果数组
       }
    return res;
}

QList<QString> SQLServer::getTableInfo(QString table){
    QList<QString> res;
    QSqlQuery q(db);
    q.exec(QString("show columns from %1 ").arg(table));
    while(q.next())
       {
          int columnNum = q.record().count();
          res.append(q.record().field(0).value().toString());//获取表头
       }
    /*for(int i = 0; i < res.size(); i++){
        qDebug()<<res.at(i);
    }*/
    return res;
}

bool SQLServer::selectSth(QString table, QJsonObject obj,QJsonArray &result){
    QString want;
    QString restriction = "";
    QJsonArray res;
    bool isDistinct = false;

    if(obj.contains("want")){
        want = obj.value("want").toString();
        if(obj.contains("isDistinct") && obj.value("isDistinct").toString().toLower() == "true"){isDistinct = true;}
        if(obj.contains("restriction")){
            restriction = obj.value("restriction").toString();
        }
        QSqlQuery q(db);
        QString content = "SELECT ";
        if(isDistinct){content += "DISTINCT ";}
        content += want;
        content += QString(" FROM %1 ").arg(table);
        if(restriction != ""){
            content += "WHERE ";
            content += restriction;
        }
        q.exec(content);
        QJsonArray res = getSQLRes(&q);
        result = res;
        qDebug()<<"Select STH!"<<content;
        return true;
    }
    return false;
}

bool SQLServer::insertSth(QString table, QJsonObject obj){
    QVariantMap map;
    for(int i = 0; i < obj.keys().size(); i++){
        QString key = obj.keys().at(i);
        QJsonValue value = obj.value(obj.keys().at(i));//因为都是jsonvalue所以没法用variant自带的判断
        map.insert(key,value);
    }
    QList<QString> SQLhead = getTableInfo(table);
    if(SQLhead.isEmpty()){
        QMessageBox::warning(nullptr,"错误",QString("表%1为空或不存在！").arg(table));
        return false;
    }
    else{
        QString insertTableContent = QString("INSERT INTO %1 (").arg(table);
        QString values = QString("VALUES (");
        for(int i = 0;i < map.keys().size(); i++){
            insertTableContent += map.keys().at(i);
            values += "'" + map.value(map.keys().at(i)).toString() + "'";
            if(i<map.keys().size()-1){insertTableContent+=",";values+=",";}
        }
        insertTableContent += ")";
        values += ") ";
        insertTableContent += values;
        qDebug()<<"INSERT STH!"<<insertTableContent;
        QSqlQuery q(db);
        return q.exec(insertTableContent);
    }
}

bool SQLServer::updateSth(QString table, QJsonObject obj){
    QVariantMap map;
    QString restriction = "";
    if(obj.contains("restriction")){
        restriction = obj.value("restriction").toString();
        obj.remove("restriction");
    }
    else {return false;}
    for(int i = 0; i < obj.keys().size(); i++){
        QString key = obj.keys().at(i);
        QJsonValue value = obj.value(obj.keys().at(i));
        map.insert(key,value);
    }
    QString content = QString("UPDATE %1 SET ").arg(table);
    QMapIterator<QString,QVariant> it(map);
    while (it.hasNext()) {
        it.next();
        content += QString("%1 = '%2'").arg(it.key()).arg(it.value().toString());
        if(it.hasNext()){content += ",";}
    }
    content += "WHERE ";
    content += restriction;
    qDebug()<<"UPDATE STH!"<<content;
    QSqlQuery q(db);
    return q.exec(content);
}

bool SQLServer::deleteSth(QString table, QJsonObject obj){
    QString restriction = "";
    if(obj.contains("restriction")){
        restriction = obj.value("restriction").toString();
    }
    else {return  false;}
    QString content = QString("DELETE FROM %1 ").arg(table);
    if(restriction.trimmed() == ""){
        return false;
    }
    else {
        content += "WHERE ";
        content += restriction;
        QSqlQuery q(db);
        qDebug()<<"DELETE STH!"<<content;
        return q.exec(content);
    }
}


