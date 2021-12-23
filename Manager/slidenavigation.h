#ifndef SLIDENAVATION_H
#define SLIDENAVATION_H

#include <QWidget>
#include <QMap>

class SlideNavigation : public QWidget
{
    Q_OBJECT

public:
    enum ItemLineStyle
    {
        None,//不显示
        ItemTop,//上方
        ItemRight,//右方
        ItemBottom,//下方
        ItemLeft,//左方
        ItemRect,//矩形
    };

    SlideNavigation(QWidget *parent = 0);
    ~SlideNavigation();

    void addItem(QString str);
    void setBarStartColor(QColor color);
    void setBarEndColor(QColor color);
    void setItemStartColor(QColor color);
    void setItemEndColor(QColor color);
    void setItemTextColor(QColor color);
    void setItemLineColor(QColor color);
    void setBarRadious(int radious);
    void setItemRadious(int radious);
    void setSpace(int space);
    void setItemLineWidth(int width);
    void setItemLineStyle(ItemLineStyle style);
    void setOrientation(Qt::Orientation orientation);
    void setFixed(bool fixed);

signals:
    void itemClicked(qintptr index, QString str);

public slots:
    void setEnableKeyMove(bool enable);
    void moveToPrevious();
    void moveToNext();
    void moveTo(int index);
    void moveTo(QString str);
    void moveTo(QPointF point);


protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void drawBarBackground(QPainter* p);//背景
    void drawItemBackground(QPainter* p);//当前选中Item背景
    void drawItemLine(QPainter* p);//ItemLine
    void drawText(QPainter* p);//all item text

private:
    void adjuseItemSize();//调整Item大小

private slots:
    void doSlide();//滑动
    void doShake();//晃动

private:
    QColor m_barStartColor;//背景色
    QColor m_barEndColor;
    QColor m_itemStartColor;//Item颜色
    QColor m_itemEndColor;
    QColor m_itemTextColor;//Item文字颜色
    QColor m_itemLineColor;//Item线条指示器颜色
    int m_barRadious;//边框圆角
    int m_itemRadious;//Item圆角
    int m_space;//Item间隔
    int m_itemLineWidth;//Item线条宽度
    ItemLineStyle m_itemLineStyle;//Item线条类型
    Qt::Orientation m_orientation;//导航方向
    bool m_enableKeyMove;//按键移动
    bool m_fixed;//固定大小

    QMap<int, QPair<QString, QRectF>> m_itemList;
    int m_totalTextWidth;//文字总长度,resize时重新计算每个Item的RectF
    int m_totalTextHeight;
    int m_currentItemIndex;//当前选中item
    QRectF m_startRect;//移动开始
    QRectF m_stopRect;//移动结束
    QTimer* m_slideTimer;//移动定时器
    QTimer* m_shakeTimer;//晃动定时器
    bool m_forward;//前进

};

#endif // SLIDENAVATION_H
