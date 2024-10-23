# 吉林大学软件学院C++课程设计
## 介绍
2021年吉林大学软件学院C++荣誉课课程设计

主题：微商系统

使用技术：C++/Qt、Mysql、TCP/IP

## 软件架构
三个大端：服务端、客户端（买家端）、业务端（卖家端）

![输入图片说明](%E6%9E%B6%E6%9E%84%E5%9B%BE.png)

### 自定义通信协议CHTTP

本次课设并没有用到HTTP，但HTTP的基本传输模式和报文格式是非常值得借鉴的。我自定义的报文协议为CHTTP，CHTTP的基本格式为A|B-CD-EF（均为数字）。其中A为状态码，仿照HTTP的格式；B为识别买家或卖家的标识；CD为操作类型，判断是购物车操作类型或是购买操作类型；EF为操作类型中的基本操作，比如将商品加入购物车、将商品删除购物车。客户端或业务端接受时第一位默认为状态码（响应报文），服务端接收时第一位默认为端表示码（请求报文）。

----

### 数据库设计

数据库名：shoppingmall

表名：

①　Users顾客名单

②　Managers管理员名单

③　Products商品表

④　Orders订单表

⑤　Orderitems订单的具体项目表

⑥　Catitems用户的购物车项目表

表的具体设计：

(1) Users顾客名单

| 列名            | 说明       | 类型    |
| --------------- | ---------- | ------- |
| User_id（主键） | 用户id     | int     |
| User_name       | 用户用户名 | varchar |
| User_password   | 用户密码   | varchar |
| User_address    | 用户地址   | varchar |
| User_money      | 用户余额   | int     |
| User_gender     | 用户性别   | enum    |

 

(2) Managers管理员名单

| 列名               | 说明         | 类型    |
| ------------------ | ------------ | ------- |
| Manager_id（主键） | 管理员id     | int     |
| Manager_name       | 管理员用户名 | varchar |
| Manager_password   | 管理员密码   | varchar |

 

(3) Products商品表

| 列名                   | 说明         | 类型    |
| ---------------------- | ------------ | ------- |
| Product_id（主键）     | 商品id       | int     |
| Product_name           | 商品名称     | varchar |
| Product_price          | 商品单价     | int     |
| Product_amount         | 商品剩余量   | int     |
| Product_sales          | 商品销量     | int     |
| Product_classification | 商品分类     | varchar |
| Product_about          | 商品描述     | varchar |
| Product_istimelimited  | 商品是否限时 | enum    |
| Product_pictureaddress | 商品图片地址 | varchar |

 

(4) Orders订单表

| 列名                  | 说明     | 类型     |
| --------------------- | -------- | -------- |
| Order_id（主键）      | 订单id   | varchar  |
| Order_user_id（外键） | 订单用户 | int      |
| Order_tolprice        | 订单总价 | int      |
| Order_status          | 订单状态 | enum     |
| Order_time            | 订单时间 | datetime |

 

(5) Orderitems订单的具体项目表

| 列名                       | 说明             | 类型    |
| -------------------------- | ---------------- | ------- |
| Orderitem_id（主键）       | 订单项目id       | int     |
| Orderitem_order_id（外键） | 订单项目的订单id | varchar |
| Orderitem_pro_id（外键）   | 订单项目的商品id | int     |
| Orderitem_num              | 订单项目购买数量 | int     |
| Orderitem_pro_price        | 订单项目单价     | int     |
| Orderitem_time             | 订单时间         | varchar |

 

(6) Catitems用户的购物车项目表

| 列名                    | 说明               | 类型 |
| ----------------------- | ------------------ | ---- |
| Catitem_id（主键）      | 购物车项目id       | int  |
| Catitem_pro_id（外键）  | 购物车项目的商品id | int  |
| Catitem_user_id（外键） | 购物车项目的用户id | int  |
| Catitem_num             | 购物车项目购买数量 | int  |

----

## 使用说明

1.  需要连Mysql数据库才能正常使用，连接mysql时记得把用户、密码啥的改为自己的数据库信息
