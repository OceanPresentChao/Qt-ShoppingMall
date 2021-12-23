#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "../shoppingclient.h"
#include <QWidget>
#include "CarouselImageWindow.h"
namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(ShoppingClient *parent = nullptr);
    ~HomePage();
    ShoppingClient *client;


private:
    Ui::HomePage *ui;

};

#endif // HOMEPAGE_H
