#include "shoppingmanager.h"
#include "ui_shoppingmanager.h"
#include<QDebug>
QString FLAG_CHARACTER = "2";//服务端标识
ShoppingManager::ShoppingManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingManager)
{
    ui->setupUi(this);
    QString style = ui->comboBox->currentText();
    this->loadStyleSheet(QString(":/qss/%1.qss").arg(style));
    ui->SideNav->setBarRadious(5);
    ui->SideNav->setItemRadious(5);
    ui->SideNav->setItemStartColor(QColor(191, 65, 249));
    ui->SideNav->setItemEndColor((QColor(187, 83, 217)));
    ui->SideNav->setOrientation(Qt::Vertical);
    ui->SideNav->addItem(tr("商品管理"));
    ui->SideNav->addItem(tr("订单管理"));
    ui->SideNav->addItem(tr("消息管理"));
    ui->SideNav->addItem(tr("资产管理"));
    ui->SideNav->setEnableKeyMove(true);//允许键盘操作
    ui->SideNav->moveTo(0);//默认选择第一项
    ui->PageStack->setCurrentIndex(0);//默认第一页

    ui->ProductP->manager = this;
    ui->OrderP->manager = this;
    ui->ContactP->manager = this;
    ui->ProsessP->manager = this;
    helpConnect();
    m_socket = new QTcpSocket();
    isconnected = false;
}

ShoppingManager::~ShoppingManager()
{
    delete ui;
}

void ShoppingManager::helpConnect(){
    connect(ui->SideNav,SIGNAL(itemClicked(qintptr,QString)),this,SLOT(changePage(qintptr)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changeStyle(int)));
}

void ShoppingManager::changePage(qintptr index){
    qintptr pagecount = ui->PageStack->count();
    if(index >= pagecount){
        ui->PageStack->setCurrentIndex(0);
    }
    else {
        ui->PageStack->setCurrentIndex(index);
    }
    //qDebug()<<ui->PageStack->currentIndex();
    return;
}

bool ShoppingManager::connectToDataBase(QString SQLkind,QString ip,int port,QString dbname,QString username,QString password){
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        db = QSqlDatabase::addDatabase(SQLkind);
    }
    db.setHostName(ip);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
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

QSqlDatabase ShoppingManager::getDataBase(){
    return this->db;
}

void ShoppingManager::closeEvent(QCloseEvent *event){
    qDebug()<<"业务端窗口关闭";
    disConnect();
    return QWidget::closeEvent(event);
}

void ShoppingManager::setServerIP(QString ip){
    server_IP = ip;
    return;
}

void ShoppingManager::setServerPort(qintptr port){
    server_port = port;
    return;
}

bool ShoppingManager::connectTo(){
    setServerIP("127.0.0.1");
    setServerPort(520);//设80会成功=。=、因为自己电脑默认80是开的
    m_socket->connectToHost(server_IP,server_port);
    if(!m_socket->waitForConnected(3000)){
        qDebug()<<"连接服务器失败！";
        QMessageBox::warning(this,tr("潮海波的通信"),tr("连接服务端失败!"),QMessageBox::Yes);
        return false;
    }
    else {
        qDebug()<<"连接服务器成功！";
        this->connectToDataBase("QMYSQL","127.0.0.1",3306,"ShoppingMall","root","chb20020309");
        isconnected = true;
        //sendCHTTPMsg("10010",QJsonObject());
    }
    return true;
}

bool ShoppingManager::disConnect(){
    m_socket->disconnectFromHost();
    if(m_socket->state() == QTcpSocket::UnconnectedState){
        isconnected = false;
        qDebug()<<"业务端断开连接成功！";
    }
    return true;
}

QByteArray ShoppingManager::sendCHTTPMsg(QString CHTTP, QJsonObject jsonobj){
    QJsonObject content;
    content.insert("head",QJsonValue(CHTTP));//设置报文头部
    content.insert("body",QJsonValue(jsonobj));//设置报文内容
    QJsonDocument document;
    document.setObject(content);
    QByteArray arr = document.toJson();
    this->m_socket->write(arr);
    if(m_socket->waitForReadyRead(5000)){
        QByteArray data = m_socket->readAll();
        qDebug()<<"客户端已成功发送消息并收到响应";
        return data;
    }else{
        QMessageBox::warning(nullptr,tr("错误！"),tr("sendCHTTP出错！"));
        return QByteArray();
    }
}

QJsonArray ShoppingManager::parseResponse(QByteArray data){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(data, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("head")) {
                QString head = object.value("head").toString();
                if(object.contains("result")){
                    QJsonValue result = object.value("result");
                    if(result.isArray()){
                        return result.toArray();
                    }
                    qDebug()<<"result:"<<object.value("result");
                }
                else{QMessageBox::warning(nullptr,tr("错误"),tr("接受数据错误！"));}
            }
        }
    }
    return QJsonArray();
}

QString ShoppingManager::parseHead(QByteArray data){
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(data, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("head")) {
                QString head = object.value("head").toString();
                if(head[0] == "1"){
                    return "1";
                }
                else if(head[0] == "2"){
                    QString errmsg = object.value("error").toString();
                    return "2"+errmsg;
                }
                else if(head[0] == "3"){
                    QString errmsg = object.value("error").toString();
                    return "3"+errmsg;
                }
            }
        }
    }
    return "";
}

void ShoppingManager::error(QChar character, QString errmsg){
    if(character == "2"){
       qDebug()<<errmsg;
       QMessageBox::warning(nullptr,"客户端错误","客户端错误:"+errmsg);
    }
    else if(character == "3"){
        qDebug()<<errmsg;
       QMessageBox::warning(nullptr,"服务端错误","服务端错误:"+errmsg);
    }
}

void ShoppingManager::someoneLogin(QJsonObject obj){
    this->show();
    this->logined_user = new Person(obj);
    qDebug()<<obj<<"Login!";
}

Person* ShoppingManager::getPerson(){
    return this->logined_user;
}

bool ShoppingManager::getConnected(){
    return this->isconnected;
}

void ShoppingManager::loadStyleSheet(const QString &styleSheetFile){
        QFile file(styleSheetFile);
        file.open(QFile::ReadOnly);
        if (file.isOpen()){
            QString styleSheet = this->styleSheet();
            styleSheet += QLatin1String(file.readAll());//读取样式表文件
            this->setStyleSheet(styleSheet);//把文件内容传参
            file.close();
        }else{
            QMessageBox::information(this,"tip","cannot find qss file");
        }
}

void ShoppingManager::changeStyle(int index){
    QString style = ui->comboBox->currentText();
    this->loadStyleSheet(QString(":/qss/%1.qss").arg(style));
}
