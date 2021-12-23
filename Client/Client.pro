#-------------------------------------------------
#
# Project created by QtCreator 2021-12-08T12:21:19
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big
SOURCES += \
        main.cpp \
    shoppingclient.cpp \
    slidenavigation.cpp\
    Cart/cartpage.cpp \
    Contact/contactpage.cpp \
    Home/carouselimagewindow.cpp \
    Home/homepage.cpp \
    Me/mepage.cpp \
    Shop/product.cpp \
    Shop/productitem.cpp \
    Shop/shoppage.cpp\
    Shop/productpage.cpp \
    Cart/cartitem.cpp \
    loginwgt.cpp \
    registerwgt.cpp \
    person.cpp \
    Me/meitem.cpp \
    Shop/textticker.cpp \
    Order/orderitem.cpp \
    Order/orderpage.cpp



HEADERS += \
    shoppingclient.h \
    slidenavigation.h\
    Cart/cartpage.h \
    Contact/contactpage.h \
    Home/carouselimagewindow.h \
    Home/homepage.h \
    Me/mepage.h \
    Shop/product.h \
    Shop/productitem.h \
    Shop/shoppage.h\
    Shop/productpage.h \
    Cart/cartitem.h \
    loginwgt.h \
    registerwgt.h \
    person.h \
    Me/meitem.h \
    Shop/textticker.h \
    Order/orderitem.h \
    Order/orderpage.h




FORMS += \
    shoppingclient.ui\
    Cart/cartpage.ui \
    Contact/contactpage.ui \
    Home/carouselimagewindow.ui \
    Home/homepage.ui \
    Me/mepage.ui \
    Shop/productitem.ui \
    Shop/shoppage.ui\
    Shop/productpage.ui \
    Cart/cartitem.ui \
    loginwgt.ui \
    registerwgt.ui \
    Me/meitem.ui \
    Order/orderitem.ui \
    Order/orderpage.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc



