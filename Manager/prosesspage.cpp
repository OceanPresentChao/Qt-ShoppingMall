#include "prosesspage.h"
#include "ui_prosesspage.h"

ProsessPage::ProsessPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProsessPage)
{
    ui->setupUi(this);
    isCached = false;

}

ProsessPage::~ProsessPage()
{
    delete ui;
}

void ProsessPage::showEvent(QShowEvent *event){
    if(!isCached){
    model = new QSqlRelationalTableModel(nullptr,manager->getDataBase());
    model->setTable("orderitems");
    model->select(); //选取整个表的所有行
    model->removeColumn(0);
    model->setRelation(1,QSqlRelation("products","pro_id","pro_name"));
    model->setRelation(4,QSqlRelation("orders","order_id","order_time"));
    model->setHeaderData(0, Qt::Horizontal, tr("订单号"));
    model->setHeaderData(1, Qt::Horizontal, tr("商品名"));
    model->setHeaderData(2, Qt::Horizontal, tr("数量"));
    model->setHeaderData(3, Qt::Horizontal, tr("单价"));
    model->setHeaderData(4, Qt::Horizontal, tr("购买时间"));
    //设置是否可以编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    //隔行变色
    ui->tableView->setAlternatingRowColors(true);
    //根据内容自动调整列宽
    ui->tableView->setSortingEnabled(true);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);
    ui->tableView->horizontalHeader()->setMaximumSectionSize(200);
    ui->treeWidget->setAlternatingRowColors(true);

    isCached = true;
    }
    else{
        model->select();
    }
    surveyData();
    connect(ui->btnBuildBarChart,SIGNAL(clicked()),this,SLOT(on_btnBuildBarChart_clicked()));
    connect(ui->btnDrawPieChart,SIGNAL(clicked()),this,SLOT(on_btnDrawPieChart_clicked()));
}

void ProsessPage::surveyData()
{ //数据统计
    ProductSaleMap.clear();
    ProductMoneyMap.clear();
    for(int i =0; i <model->rowCount(); i++){
        for(int j = 2;j<= 3; j++)
        {
            int val=model->data(model->index(i,j)).toInt();
            QString name = model->data(model->index(i,1)).toString();
            ////////////////////////////
            //统计销量
            if (j == 2)
            {
                if(ProductSaleMap.contains(name)){
                    ProductSaleMap.insert(name,ProductSaleMap.value(name)+val);
                }
                else{
                    ProductSaleMap.insert(name,val);
                }
            }
            //统计金额
            if(j == 3){
                if(ProductMoneyMap.contains(name)){
                    ProductMoneyMap.insert(name,ProductMoneyMap.value(name)+val);
                }
                else{
                    ProductMoneyMap.insert(name,val);
                }
            }
        }
    }
    for(int i = 0;i < ProductSaleMap.size(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem(); //节点
        item->setText(0,ProductSaleMap.keys().at(i));
        item->setTextAlignment(0,Qt::AlignHCenter);
        item->setText(1,QString::number(ProductSaleMap.value(ProductSaleMap.keys().at(i)))+"件");
        item->setTextAlignment(1,Qt::AlignHCenter);
        item->setText(2,QString::number(ProductMoneyMap.value(ProductSaleMap.keys().at(i)))+"元");
        item->setTextAlignment(2,Qt::AlignHCenter);
        ui->treeWidget->addTopLevelItem(item);
    }
    qDebug()<<ProductSaleMap.size();
    qDebug()<<ProductMoneyMap.size();
}

void ProsessPage::iniBarChart()
{ //柱状图初始化
    QChart *chart = new QChart(); //创建chart
    chart->setTitle("商品销量盈利柱状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar->setChart(chart); //为ChartView设置chart
    ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
}

void ProsessPage::buildBarChart()
{ //构造柱状图
    QChart *chart =ui->chartViewBar->chart(); //获取ChartView关联的chart
    chart->removeAllSeries(); //删除所有序列

    chart->removeAxis(chart->axisX()); //删除坐标轴
    chart->removeAxis(chart->axisY()); //删除坐标轴

//创建三个QBarSet数据集,从数据模型的表头获取Name
    QBarSet *setSale = new QBarSet("销量");//销量表头
    QBarSet *setMoney = new QBarSet("盈利");//盈利表头

    //用于横坐标在字符串列表,即商品姓名
    QStringList categories;
    for(int i=0;i<ProductSaleMap.size();i++)
    {//从数据模型获取数据
        //分类名称
        categories <<ProductSaleMap.keys().at(i);
        setSale->append(ProductSaleMap.value(ProductSaleMap.keys().at(i))); //销量
        setMoney->append(ProductMoneyMap.value(ProductSaleMap.keys().at(i))); //盈利
    }

//创建一个柱状图序列 QBarSeries, 并添加三个数据集
    QBarSeries *series = new QBarSeries();
    series->append(setSale);
    series->append(setMoney);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsCenter);// LabelsCenter
    chart->addSeries(series); //添加柱状图序列

//用于柱状图的坐标轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories); //添加横坐标文字列表
//    chart->createDefaultAxes();
    chart->setAxisX(axisX, series); //设置横坐标
    axisX->setRange(categories.at(0), categories.at(categories.count()-1)); //这只坐标轴范围

//数值型坐标作为纵轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100);
    axisY->setTitleText("元/件");
    axisY->setTickCount(6);//11
    axisY->setLabelFormat("%.0f"); //标签格式
//    axisY->setGridLineVisible(false);
//    axisY->setMinorTickCount(4);
    chart->setAxisY(axisY, series); //

    chart->legend()->setVisible(true); //显示图例
    chart->legend()->setAlignment(Qt::AlignBottom); //图例显示在下方
}


void ProsessPage::iniPiewChart()
{ //饼图初始化
    QChart *chart = new QChart();
    chart->setTitle("商品销量饼状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewPie->setChart(chart);
    ui->chartViewPie->setRenderHint(QPainter::Antialiasing);

    QChart *chart2 = new QChart();
    chart2->setTitle("商品盈利饼状图");
    chart2->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewPie2->setChart(chart2);
    ui->chartViewPie2->setRenderHint(QPainter::Antialiasing);
}

void ProsessPage::buildPieChart()
{ //绘制饼图
    QChart *chart =ui->chartViewPie->chart(); //获取chart对象
    chart->removeAllSeries(); //删除所有序列

    QPieSeries *series = new QPieSeries(); //创建饼图序列
    series->setHoleSize(ui->spinHoleSize->value()); //饼图中间空心的大小

    for (int i=0;i<ProductSaleMap.size();i++) //添加分块数据,统计销量
    {
        QString name = ProductSaleMap.keys().at(i);
        series->append(name,ProductSaleMap.value(name)); //添加一个饼图分块数据,标签，数值
    }

    QPieSlice *slice; //饼图分块
    for(int i=0;i<ProductSaleMap.size();i++) //设置每个分块的标签文字
    {
        slice =series->slices().at(i);  //获取分块
        slice->setLabel(slice->label()+QString::asprintf(": %.0f件, %.1f%%",    //设置分块的标签
                        slice->value(),slice->percentage()*100));
//信号与槽函数关联，鼠标落在某个分块上时，此分块弹出
        connect(slice, SIGNAL(hovered(bool)),this, SLOT(on_PieSliceHighlight(bool)));
    }
    slice->setExploded(true); //最后一个设置为exploded
    series->setLabelsVisible(true); //只影响当前的slices，必须添加完slice之后再设置
    chart->addSeries(series); //添加饼图序列
    chart->setTitle("商品销量饼状图");

    chart->legend()->setVisible(true); //图例
    chart->legend()->setAlignment(Qt::AlignRight);//Qt::AlignRight


    QChart *chart2 =ui->chartViewPie2->chart(); //获取chart对象
    chart2->removeAllSeries(); //删除所有序列

    QPieSeries *series2 = new QPieSeries(); //创建饼图序列
    series2->setHoleSize(ui->spinHoleSize->value()); //饼图中间空心的大小

    for (int i=0;i<ProductMoneyMap.size();i++) //添加分块数据,统计销量
    {
        QString name = ProductMoneyMap.keys().at(i);
        series2->append(name,ProductMoneyMap.value(name)); //添加一个饼图分块数据,标签，数值
    }

    QPieSlice *slice2; //饼图分块
    for(int i=0;i<ProductMoneyMap.size();i++) //设置每个分块的标签文字
    {
        slice2 =series2->slices().at(i);  //获取分块
        slice2->setLabel(slice2->label()+QString::asprintf(": %.0f元, %.1f%%",    //设置分块的标签
                        slice2->value(),slice2->percentage()*100));
//信号与槽函数关联，鼠标落在某个分块上时，此分块弹出
        connect(slice2, SIGNAL(hovered(bool)),this, SLOT(on_PieSliceHighlight(bool)));
    }
    slice2->setExploded(true); //最后一个设置为exploded
    series2->setLabelsVisible(true); //只影响当前的slices，必须添加完slice之后再设置
    chart2->addSeries(series2); //添加饼图序列
    chart2->setTitle("商品盈利饼状图");

    chart2->legend()->setVisible(true); //图例
    chart2->legend()->setAlignment(Qt::AlignRight);//Qt::AlignRight
}

void ProsessPage::on_btnBuildBarChart_clicked()
{
    buildBarChart();
}

void ProsessPage::on_btnDrawPieChart_clicked()
{
    buildPieChart();
}

void ProsessPage::on_spinHoleSize_valueChanged(double arg1)
{
    QPieSeries  *series;
    series=(QPieSeries*)ui->chartViewPie->chart()->series().at(0);
    series->setHoleSize(arg1);

    QPieSeries  *series2;
    series2=(QPieSeries*)ui->chartViewPie2->chart()->series().at(0);
    series2->setHoleSize(arg1);
}

void ProsessPage::on_spinPieSize_valueChanged(double arg1)
{
    QPieSeries  *series;
    series=(QPieSeries*)ui->chartViewPie->chart()->series().at(0);
    series->setPieSize(arg1);

    QPieSeries  *series2;
    series2=(QPieSeries*)ui->chartViewPie2->chart()->series().at(0);
    series2->setPieSize(arg1);
}

void ProsessPage::on_cBoxTheme_currentIndexChanged(int index)
{
    ui->chartViewPie->chart()->setTheme(QChart::ChartTheme(index));

    ui->chartViewPie2->chart()->setTheme(QChart::ChartTheme(index));
}

void ProsessPage::on_PieSliceHighlight(bool show)
{ //鼠标移入、移出时触发hovered()信号，动态设置setExploded()效果
    QPieSlice *slice;
    slice=(QPieSlice *)sender();
//    slice->setLabelVisible(show);
    slice->setExploded(show);
}

void ProsessPage::on_chartBarLegendMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type())
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
            marker->series()->setVisible(!marker->series()->isVisible());
            marker->setVisible(true);
            break;
        }

        case QLegendMarker::LegendMarkerTypeBar:
        { //bar不好处理, barset不能被隐藏，只能take，但是无法恢复
            marker->series()->setVisible(!marker->series()->isVisible());
            marker->setVisible(true);
            break;
        }

        default:
            break;
    }

}
