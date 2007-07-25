TEMPLATE = app
TARGET = momple
CONFIG += qt

include(../conf.pri)

#INCLUDEPATH = /usr/include/lua5.1;../../bindings#;/usr/include/wx-2.6
#LIBS += lua5.1# wx_baseu-2.6

HEADERS += connectionmanager.h \
           mainwindow.h \
           signinwidget.h \
           statuswidget.h \
           contact.h \
           contactwidget.h# \
#           luainterface.h \
#           tessaguiservices.h
SOURCES += connectionmanager.cpp \
           main.cpp \
           mainwindow.cpp \
           signinwidget.cpp \
           statuswidget.cpp \
           contact.cpp \
           contactwidget.cpp# \
#           luainterface.cpp
RESOURCES += $$PWD/../icons/icons.qrc \
             $$PWD/../images/images.qrc \
             $$PWD/../styles/styles.qrc

unix:!mac {
  QMAKE_POST_LINK = rm -f ../momple; ln -s src/momple ../momple
}
