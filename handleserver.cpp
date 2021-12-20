#include "handleserver.h"
#include<QtDebug>
HandleServer::HandleServer(SQLServer* sqlserver)
{
    this->sql = sqlserver;
}


void HandleServer::handleRequest(const QString& ip,const qintptr port, const QByteArray data){
        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);  // 转化为 JSON 文档
        if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (document.isObject()) {  // JSON 文档为对象
                QJsonObject object = document.object();  // 转化为对象
                QString strHead;//头部报文
                if (object.contains("head")) {//处理头部
                    QJsonValue value = object.value("head");
                    strHead = value.toString();
                    if(strHead.length() != 5){jsonResReady("2",QJsonArray(),port,"协议码长度错误！");return;}
                    qDebug() << "head : " << strHead;
                }
                else{jsonResReady("2",QJsonArray(),port,"没有报文头部！");return;}
                if(object.contains("body")){//处理主体
                    int flag_character = strHead.mid(0,1).toInt();//端标识码
                    int flag_inskind = strHead.mid(1,2).toInt();//行为类型标识码
                    int flag_ins = strHead.mid(3,2).toInt();//操作码
                    QJsonObject body = object.value("body").toObject();
                    switch (flag_inskind) {
                    case 1://登入或登出
                        switch (flag_ins) {
                        case 1:
                            handleLogin(body,port);
                            break;
                        case 2:
                            handleRegister(body,port);
                            break;
                        default:
                            jsonResReady("2",QJsonArray(),port,"不合法的报文！");
                            break;
                        }
                        break;

                    case 2://操作商品
                        switch (flag_ins) {
                        case 4:
                            handleSearchProduct(body,port);
                            break;
                        case 5:
                            handleBuySth(body,port);
                            break;
                        default:
                            break;
                        }
                        break;

                    case 3://操作购物车
                        switch (flag_ins) {
                        case 1:
                            handleAddCart(body,port);
                            break;
                        case 2:
                            handleDelCart(body,port);
                            break;
                        case 3:
                            handleUpdateCart(body,port);
                            break;
                        case 4:
                            handleSearchCart(body,port);
                            break;
                        default:
                            break;
                        }
                        break;
                    case 4:
                        switch (flag_ins) {
                        case 4:
                            handleSearchOrder(body,port);
                            break;
                        case 5:
                            handleSearchOrderItems(body,port);
                            break;
                        }
                        break;
                    }
                }
                else{jsonResReady("2",QJsonArray(),port,"没有报文主体！");return;}
            }
        }
        else{jsonResReady("3",QJsonArray(),port,"解析错误！");return;}
}

void HandleServer::jsonResReady(QString head,QJsonArray res,qintptr port,QString errmsg){
    QJsonObject response;
    response.insert("head",head);
    if(head[0] == "3"){//服务端出错
        response.insert("error",QJsonValue(errmsg));
    }
    else if(head[0] == "2"){//客户端出错
        response.insert("error",QJsonValue(QString(errmsg)));
    }
    else if(head[0] == "1"){//成功
        response.insert("result",QJsonValue(res));
    }
    QJsonDocument document;
    document.setObject(response);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    emit signal_responeReady(byteArray,port);
}

void HandleServer::handleLogin(QJsonObject body, qintptr port){
    QString table = "users";
    QJsonArray res;
    bool flag = sql->selectSth(table,body,res);
    if(flag){
        jsonResReady("1",res,port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询用户名失败！");return;}
}

void HandleServer::handleRegister(QJsonObject body, qintptr port){
    QString table = "users";
    QJsonArray res;
    if(body.contains("user_name")){
        QJsonObject obj;
        QString _name = obj.value("user_name").toString();
        obj.insert("want",QJsonValue("user_name"));
        obj.insert("isDistinct",QJsonValue("true"));
        obj.insert("restriction",QJsonValue(QString("user_name = '%1'").arg(_name)));
        QJsonArray search;
        bool fl = sql->selectSth(table,obj,search);
        if(fl){
            if(!search.isEmpty()){
                jsonResReady("2",QJsonArray(),port,"该用户名已被注册！");
                return;
            }
        }
        else{
            jsonResReady("3",QJsonArray(),port,"查询用户名失败！");
            return;
        }
    }
    bool flag = sql->insertSth(table,body);
    if(flag){
        jsonResReady("1",QJsonArray(),port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询用户名失败！");return;}
}

void HandleServer::handleSearchProduct(QJsonObject body, qintptr port){
    QString table = "products";
    QJsonArray result;
    bool flag = sql->selectSth(table,body,result);
    if(flag){
        jsonResReady("1",result,port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询商品失败！");return;}
}

void HandleServer::handleAddCart(QJsonObject body, qintptr port){
    QString table = "cartitems";
    bool flag = sql->insertSth(table,body);
    if(flag){
        jsonResReady("1",QJsonArray(),port);
    }
    else{jsonResReady("3",QJsonArray(),port,"插入购物车失败！");return;}
}

void HandleServer::handleDelCart(QJsonObject body, qintptr port){
    QString table = "cartitems";
    bool flag = sql->deleteSth(table,body);
    if(flag){
        jsonResReady("1",QJsonArray(),port);
    }
    else{jsonResReady("3",QJsonArray(),port,"删除购物车失败！");return;}
}

void HandleServer::handleUpdateCart(QJsonObject body, qintptr port){
    QString table = "cartitems";
    bool flag = sql->updateSth(table,body);
    if(flag){
        jsonResReady("1",QJsonArray(),port);
    }
    else{jsonResReady("3",QJsonArray(),port,"更新购物车失败！");return;}
}

void HandleServer::handleSearchCart(QJsonObject body, qintptr port){
    QString table = "products,cartitems";
    QJsonArray result;
    bool flag = sql->selectSth(table,body,result);
    if(flag){
        jsonResReady("1",result,port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询购物车失败！");return;}
}

void HandleServer::handleBuySth(QJsonObject body, qintptr port){
    if(!body.contains("type")){
        jsonResReady("2",QJsonArray(),port,"需指定购买类型！");return;
    }
    QString type = body.value("type").toString().toLower();
    if(type == "cart"){
        //查询用户余额
        QJsonArray _result,_allwant;
        QJsonObject obj1,obj2;
        int _user_id = body.value("user_id").toString().toInt();
        obj1.insert("want",QJsonValue("user_money"));
        obj1.insert("restriction",QJsonValue(QString("user_id = '%1'").arg(_user_id)));
        bool flag = sql->selectSth("users",obj1,_result);
        if(!flag){
            jsonResReady("3",QJsonArray(),port,"查询用户失败！");return;
        }
        int money = _result[0].toObject().value("user_money").toString().toInt();
        //查询用户购物车
        obj2.insert("want",QJsonValue("cart_pro_id,pro_name,pro_amount,pro_sales,cart_num,pro_price,pro_price*cart_num AS pro_tolprice"));
        obj2.insert("restriction",QJsonValue(QString("products.pro_id = cartitems.cart_pro_id AND cart_user_id = user_id AND user_id = %1").arg(_user_id)));
        flag = sql->selectSth("users,products,cartitems",obj2,_allwant);
        if(!flag){
             jsonResReady("3",QJsonArray(),port,"查询用户失败！");return;
        }
        if(_allwant.isEmpty()){jsonResReady("3",QJsonArray(),port,"查询数据失败！");return;}
        int tolprice = 0;
        QJsonArray wannabuy = body.value("wannabuy").toArray();
        //将用户的整个购物车信息转换成map
        QJsonObject map;
        for(int i = 0;i < _allwant.size(); i++){
            QJsonObject tmpobj = _allwant[i].toObject();
            map.insert(tmpobj.value("cart_pro_id").toString(),tmpobj);
        }
        for(int i = 0;i < wannabuy.size(); i++){
            QJsonObject _obj = map.value(wannabuy[i].toString()).toObject();
            int _cart_num = _obj.value("cart_num").toString().toInt();
            int _pro_num = _obj.value("pro_amount").toString().toInt();
            QString _pro_name = _obj.value("pro_name").toString();
            if(_cart_num > _pro_num || _pro_num == 0){jsonResReady("2",QJsonArray(),port,QString("%1商品余量不足！").arg(_pro_name));return;}//检查购物车每个商品数量
            tolprice += _obj.value("pro_tolprice").toString().toInt();//遍历wannabuy里的项目的金额算出总金额
        }
        //qDebug()<<"tolprice:"<<tolprice<<"money"<<money;
        if(money >= tolprice){
            //更新用户金额数据
            QJsonObject obj3;
            obj3.insert("user_money",QJsonValue(QString::number(money - tolprice)));
            obj3.insert("restriction",QJsonValue(QString("user_id = %1").arg(_user_id)));            
            flag = sql->updateSth("users",obj3);
            if(!flag){
                 jsonResReady("3",QJsonArray(),port,"更新用户金额失败！");return;
            }
            QJsonArray response;
            response.push_back(QJsonValue(money - tolprice));
            response.push_back(QJsonValue(tolprice));
            jsonResReady("1",response,port);
            qDebug()<<"购买成功！"<<"tolprice:"<<tolprice<<"money"<<money;
            //更新商品余量和销量
            for(int i = 0;i < wannabuy.size(); i++){
                QJsonObject tmpobj = map.value(wannabuy[i].toString()).toObject();
                int _cart_num = tmpobj.value("cart_num").toString().toInt();
                int _pro_num = tmpobj.value("pro_amount").toString().toInt();
                int _pro_sale = tmpobj.value("pro_sales").toString().toInt();
                int _pro_id = tmpobj.value("cart_pro_id").toString().toInt();
                QJsonObject obj5;
                obj5.insert("pro_amount",QJsonValue(QString::number(_pro_num - _cart_num)));
                obj5.insert("pro_sales",QJsonValue(QString::number(_pro_sale + _cart_num)));
                obj5.insert("restriction",QJsonValue(QString("pro_id = %1").arg(_pro_id)));
                flag = sql->updateSth("products",obj5);
                if(!flag){
                     jsonResReady("3",QJsonArray(),port,"更新商品失败！");return;
                }
            }
            //删除购买了的购物车类
            QJsonObject obj4;
            QString delSQL = QString("cart_user_id = %1 AND (").arg(_user_id);
            for(int i = 0;i < wannabuy.size(); i++){
                delSQL += QString("cart_pro_id = %1").arg(wannabuy[i].toString());
                if(i < wannabuy.size()-1){delSQL += " OR ";}
            }
            delSQL += ")";
            obj4.insert("restriction",QJsonValue(delSQL));
            flag = sql->deleteSth("cartitems",obj4);
            if(!flag){
                 jsonResReady("3",QJsonArray(),port,"更新用户数据失败！");return;
            }
            //生成订单
            QJsonObject order_obj;
            QDateTime curDateTime=QDateTime::currentDateTime();
            QString ordernum = getRandomOrderNum();
            order_obj.insert("order_time",curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
            order_obj.insert("order_user_id",QString::number(_user_id));
            order_obj.insert("order_tolprice",QString::number(tolprice));
            order_obj.insert("order_id",ordernum);
            bool flag = sql->insertSth("orders",order_obj);
            if(flag && createOrderItems(wannabuy,map,ordernum)){
                jsonResReady("1",QJsonArray(),port);
            }
            else{jsonResReady("3",QJsonArray(),port,"更新订单失败！");return;}
        }
        else{jsonResReady("2",QJsonArray(),port,"您的余额不足！");qDebug()<<"余额不足！";}
    }
}

bool HandleServer::createOrderItems(QJsonArray wannabuy,QJsonObject map,QString ordernum){
    bool res = true;
    for(int i = 0;i < wannabuy.size(); i++){
        QJsonObject _obj = map.value(wannabuy[i].toString()).toObject();
        int _cart_num = _obj.value("cart_num").toString().toInt();
        int _pro_id = _obj.value("cart_pro_id").toString().toInt();
        int _pro_price = _obj.value("pro_price").toString().toInt();
        QJsonObject _item;
        _item.insert("orderitem_order_id",QJsonValue(ordernum));
        _item.insert("orderitem_pro_id",QJsonValue(QString::number(_pro_id)));
        _item.insert("orderitem_num",QJsonValue(QString::number(_cart_num)));
        _item.insert("orderitem_pro_price",QJsonValue(QString::number(_pro_price)));
        bool flag = sql->insertSth("orderitems",_item);
        res = flag == true ? true:false;
    }
    return res;
}

QString HandleServer::getRandomOrderNum(){
    QJsonObject obj;
    QString context = "CONCAT('SD',DATE_FORMAT(now(), '%Y%m%d%H%i%s'),lpad(round(round(rand(),4)*1000),4,'0'))";
    obj.insert("want",context);
    QJsonArray result;
    bool flag = sql->selectSth("dual",obj,result);
    if(!flag){return "error";}
    return result[0].toObject().value(context).toString();
}

void HandleServer::handleSearchOrder(QJsonObject body,qintptr port){
    QString table = "orders";
    QJsonArray result;
    bool flag = sql->selectSth(table,body,result);
    if(flag){
        jsonResReady("1",result,port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询订单失败！");return;}
}

void HandleServer::handleSearchOrderItems(QJsonObject body, qintptr port){
    QString table = "orders,orderitems,products";
    QJsonArray result;
    bool flag = sql->selectSth(table,body,result);
    qDebug()<<"orderitems num:"<<result.size();
    if(flag){
        jsonResReady("1",result,port);
    }
    else{jsonResReady("3",QJsonArray(),port,"查询订单信息失败！");return;}
}
