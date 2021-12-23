#include "shoppingclient.h"
#include"loginwgt.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(qApp->applicationDirPath());
    ShoppingClient w;
    LoginWgt q(&w);
    q.show();
    return a.exec();
}
