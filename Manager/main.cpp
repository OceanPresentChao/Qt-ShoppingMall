#include "shoppingmanager.h"
#include"loginwgt.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Manager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    ShoppingManager w;
    LoginWgt q(&w);
    q.show();
    return a.exec();
}
