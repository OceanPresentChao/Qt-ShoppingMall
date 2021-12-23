#ifndef ProductItem_H
#define ProductItem_H

#include <QWidget>
#include<QMouseEvent>
#include"textticker.h"
namespace Ui {
class ProductItem;
}

class ProductItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProductItem(QWidget *parent = nullptr);
    ~ProductItem();
    void setLabNumColor(bool bo); //设置样式
    void setLabNumText(QString str);
    void setLabNameText(QString str);
    void setLabrankingText(QString str);
    void setLabMessageText(QString str);
    void setId(QString id);
    int getId();
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    Ui::ProductItem *ui;
    int id;
signals:
    void signal_proitem_dblclick(int);
};

#endif // ProductItem_H
