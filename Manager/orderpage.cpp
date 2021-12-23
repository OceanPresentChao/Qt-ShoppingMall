#include "orderpage.h"
#include "ui_orderpage.h"

OrderPage::OrderPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderPage)
{
    ui->setupUi(this);
    isCached = false;
}

OrderPage::~OrderPage()
{
    delete ui;
}

void OrderPage::showEvent(QShowEvent *event){
    if(!isCached){
    model = new QSqlRelationalTableModel(nullptr,manager->getDataBase());
    model->setTable("orders");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    //model->setRelation(1,QSqlRelation("users","user_id","user_name"));
    //ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    //不显示name属性列,如果这时添加记录，则该属性的值添加不上
    // model->removeColumn(1);
    ui->tableView->setModel(model);
    //使其不可编辑
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隔行变色
    ui->tableView->setAlternatingRowColors(true);
    //根据内容自动调整列宽
    ui->tableView->setSortingEnabled(true);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);
    ui->tableView->horizontalHeader()->setMaximumSectionSize(200);

    connect(ui->btn_back,SIGNAL(clicked()),this,SLOT(backChange()));
    connect(ui->btn_search,SIGNAL(clicked()),this,SLOT(searchOrder()));
    connect(ui->btn_submit,SIGNAL(clicked()),this,SLOT(submitChange()));
    connect(ui->btn_refresh,SIGNAL(clicked()),this,SLOT(refreshOrder()));
    isCached = true;
    }
}

void OrderPage::submitChange(){
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) {
       model->database().commit(); //提交
    } else {
       model->database().rollback(); //回滚
       QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

void OrderPage::backChange(){
    model->revertAll();
}

void OrderPage::searchOrder(){
    QString restriction = ui->lineEdit->text();
    //根据进行筛选
    model->setFilter(restriction);
    //显示结果
    model->select();
}

void OrderPage::refreshOrder(){
    model->select(); //选取整个表的所有行
}
