#include "registerwgt.h"
#include "ui_registerwgt.h"

RegisterWgt::RegisterWgt(ShoppingClient *p) :
    ui(new Ui::RegisterWgt)
{
    ui->setupUi(this);
    client = p;
    QRegExp ps("^[A-Za-z0-9]+$");//由数字和26个英文字母组成的字符串
    QRegExp us("^[A-Za-z0-9\u4e00-\u9fa5]+$");
    QRegExpValidator *latitude1 = new QRegExpValidator(us, this);
    QRegExpValidator *latitude2 = new QRegExpValidator(ps, this);
    ui->line_name->setValidator(latitude1);
    ui->line_password->setValidator(latitude2);
    ui->line_repassword->setValidator(latitude2);
    ui->line_add->setValidator(latitude1);
    connect(ui->btn_register,SIGNAL(clicked()),this,SLOT(registerUser()));
}

RegisterWgt::~RegisterWgt()
{
    delete ui;
}

void RegisterWgt::paintEvent(QPaintEvent*)
{
    QPainter paint_win(this);
    QPixmap map_win;
    map_win.load(":/images/login/7.png");
    paint_win.drawPixmap(0,0,this->width(),this->height(),map_win);
}

void RegisterWgt::registerUser(){
    QString dlgTitle="Question消息框";
    QString strInfo="是否确定注册？";
    QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
    QMessageBox::StandardButton result;//返回选择的按钮
    result=QMessageBox::question(this, dlgTitle, strInfo,QMessageBox::Yes|QMessageBox::Cancel,defaultBtn);
    if(result==QMessageBox::Yes){
        if(!client->getConnected()){QMessageBox::warning(nullptr,"错误","未连接到网络！");return;}
        QString _password = ui->line_password->text();
        QString _repassword = ui->line_repassword->text();
        QString _name = ui->line_name->text();
        QString _add = ui->line_add->text();
        QString _gender = ui->combox_render->currentText();
        if(_password == "" || _repassword == "" || _name == "" || _add == ""){
            QMessageBox::warning(nullptr,"错误","请确保每项都已填写！");
            return;
        }
        if(_password != _repassword){
            QMessageBox::warning(nullptr,"错误","请确保两次输入的密码一致！");
            return;
        }

        QJsonObject obj;
        //qDebug()<<sql;
        obj.insert("user_name",QJsonValue(_name));
        obj.insert("user_password",QJsonValue(_password));
        obj.insert("user_address",QJsonValue(_add));
        obj.insert("user_gender",QJsonValue(_gender));
        QByteArray data = client->sendCHTTPMsg("10102",obj);//注册
        QString flag = client->parseHead(data);
        if(flag[0] != "1"){
            if(flag[0] == "2"){
               QMessageBox::warning(nullptr,"注册失败","客户端错误:"+flag.mid(1));
            }
            else if(flag[0] == "3"){
               QMessageBox::warning(nullptr,"注册失败","服务端错误:"+flag.mid(1));
            }
            return;
        }
        else{
            QMessageBox::information(nullptr,"注册成功","注册成功！");
            this->close();
        }
    }
}
