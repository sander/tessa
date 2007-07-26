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
           LuaInterface.h \
           TessaGUIServices.h \
           tessacorethread.h
SOURCES += connectionmanager.cpp \
           main.cpp \
           mainwindow.cpp \
           signinwidget.cpp \
           statuswidget.cpp \
           contact.cpp \
           contactwidget.cpp \
           LuaInterface.cpp \
           tessacorethread.cpp
RESOURCES += $$PWD/../icons/icons.qrc \
             $$PWD/../images/images.qrc \
             $$PWD/../styles/styles.qrc

unix:!mac {
  QMAKE_POST_LINK = rm -f ../momple; ln -s src/momple ../momple
}
