#ifndef MEITEM_H
#define MEITEM_H

#include <QWidget>

namespace Ui {
class MeItem;
}

class MeItem : public QWidget
{
    Q_OBJECT

public:
    explicit MeItem(QWidget *parent = nullptr);
    ~MeItem();
    void setKey(QString);
    void setVal(int);
    void setVal(QString);
    void setPic(QString);


private:
    Ui::MeItem *ui;
};

#endif // MEITEM_H
