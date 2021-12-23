#include "productpage.h"
#include "ui_productpage.h"

ProductPage::ProductPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductPage)
{
    ui->setupUi(this);
    isCached = false;
}

ProductPage::~ProductPage()
{
    delete ui;
}

void ProductPage::showEvent(QShowEvent *event){
    if(!isCached){
    model = new QSqlTableModel(nullptr,manager->getDataBase());
    model->setTable("products");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
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
    connect(ui->btn_search,SIGNAL(clicked()),this,SLOT(searchProduct()));
    connect(ui->btn_submit,SIGNAL(clicked()),this,SLOT(submitChange()));
    connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(addProduct()));
    connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(delProduct()));
    isCached = true;
    }
}

void ProductPage::submitChange(){
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) {
       model->database().commit(); //提交
    } else {
       model->database().rollback(); //回滚
       QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

void ProductPage::backChange(){
    model->revertAll();
}

void ProductPage::addProduct(){
    int rowNum = model->rowCount(); //获得表的行数
    model->insertRow(rowNum); //添加一行
    //model->submitAll(); //可以直接提交
}

void ProductPage::delProduct(){
    //获取选中的行
    int curRow = ui->tableView->currentIndex().row();

    //删除该行
    model->removeRow(curRow);

    int ok = QMessageBox::warning(this,tr("提醒"),tr("你确定""下线该产品吗？"),QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           model->revertAll(); //如果不删除，则撤销
        }
        else model->submitAll(); //否则提交，在数据库中删除该行
}

void ProductPage::searchProduct(){
    QString restriction = ui->lineEdit->text();
    //根据姓名进行筛选
    model->setFilter(restriction);
    //显示结果
    model->select();
}
