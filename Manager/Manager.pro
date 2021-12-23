QT       += core gui
QT       += sql
QT       += network
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contactpage.cpp \
    main.cpp \
    orderpage.cpp \
    productpage.cpp \
    prosesspage.cpp \
    shoppingmanager.cpp \
    slidenavigation.cpp \
    loginwgt.cpp \
    person.cpp

HEADERS += \
    contactpage.h \
    orderpage.h \
    productpage.h \
    prosesspage.h \
    shoppingmanager.h \
    slidenavigation.h \
    loginwgt.h \
    person.h

FORMS += \
    contactpage.ui \
    orderpage.ui \
    productpage.ui \
    prosesspage.ui \
    shoppingmanager.ui \
    loginwgt.ui

TRANSLATIONS += \
    Manager_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
