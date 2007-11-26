TEMPLATE = app
TARGET = momple
CONFIG += qt

MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rcc

include(../conf.pri)

#INCLUDEPATH = /usr/include/lua5.1;../../bindings
#LIBS += -llua5.1

HEADERS += \
           mainwindow.h \
           signinwidget.h \
           statuswidget.h \
           contact.h \
           contactwidget.h \
#           luathread.h \
           accountwidget.h \
	   contactactionwidget.h \
	   footerwidget.h
SOURCES += \
           main.cpp \
           mainwindow.cpp \
           signinwidget.cpp \
           statuswidget.cpp \
           contact.cpp \
           contactwidget.cpp \
#           luathread.cpp \
           accountwidget.cpp \
	   contactactionwidget.cpp \
	   footerwidget.cpp
RESOURCES += \
             $$PWD/../icons/icons.qrc \
			 $$PWD/../styles/styles.qrc

unix:!mac {
	QMAKE_POST_LINK = rm -f ../momple; ln -s src/momple ../momple
	QMAKE_CLEAN = ../momple
}
