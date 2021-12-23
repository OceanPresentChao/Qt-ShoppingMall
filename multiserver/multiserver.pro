QT       += core gui network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMultiThreadTcpServer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    mysocket.cpp \
    tcpserver.cpp \
    server.cpp \
    tcpserverthread.cpp \
    sqlserver.cpp \
    udpserver.cpp \
    handleserver.cpp


HEADERS  += dialog.h \
    mysocket.h \
    tcpserver.h \
    server.h \
    tcpserverthread.h \
    sqlserver.h \
    udpserver.h \
    handleserver.h


FORMS    += dialog.ui \

