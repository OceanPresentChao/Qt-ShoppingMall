#ifndef PROSESSPAGE_H
#define PROSESSPAGE_H

#include <QWidget>
#include<QtCharts>
#include<QChartView>
#include<QValueAxis>
#include<QSqlRelationalTableModel>
#include<QSqlError>
#include<QSqlRelationalDelegate>
#include"shoppingmanager.h"
#include    <QTime>
#include    <QBarSet>
#include    <QInputDialog>
#include <QMap>
QT_CHARTS_USE_NAMESPACE//使用宏定义
namespace Ui {
class ProsessPage;
}

class ProsessPage : public QWidget
{
    Q_OBJECT
public:
    explicit ProsessPage(QWidget *parent = nullptr);
    ~ProsessPage();
    ShoppingManager *manager;
    void showEvent(QShowEvent *event);

private:
    Ui::ProsessPage *ui;
    QSqlRelationalTableModel *model;
    bool isCached;
    QMap<QString,int> ProductSaleMap;
    QMap<QString,int> ProductMoneyMap;
    void    surveyData();//统计数据

    void    iniBarChart(); //柱状图初始化
    void    buildBarChart();//构建柱状图

    void    iniPiewChart(); //饼图初始化
    void    buildPieChart(); //构建饼图

private slots:

    void on_PieSliceHighlight(bool show);

    void on_chartBarLegendMarkerClicked();

    void on_btnBuildBarChart_clicked();

    void on_btnDrawPieChart_clicked();

    void on_spinHoleSize_valueChanged(double arg1);

    void on_spinPieSize_valueChanged(double arg1);

    void on_cBoxTheme_currentIndexChanged(int index);
};

#endif // PROSESSPAGE_H
