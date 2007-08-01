TEMPLATE = app
TARGET = momple
CONFIG += qt

include(../conf.pri)

INCLUDEPATH = /usr/include/lua5.1;../../bindings
LIBS += -llua5.1

HEADERS += connectionmanager.h \
           mainwindow.h \
           signinwidget.h \
           statuswidget.h \
           contact.h \
           contactwidget.h \
           luathread.h \
           accountwidget.h
SOURCES += connectionmanager.cpp \
           main.cpp \
           mainwindow.cpp \
           signinwidget.cpp \
           statuswidget.cpp \
           contact.cpp \
           contactwidget.cpp \
           luathread.cpp \
           accountwidget.cpp
RESOURCES += $$PWD/../icons/icons.qrc

unix:!mac {
  QMAKE_POST_LINK = rm -f ../momple; ln -s src/momple ../momple
}
