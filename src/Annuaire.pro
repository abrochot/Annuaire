#-------------------------------------------------
#
# Project created by QtCreator 2011-05-07T22:16:30
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Annuaire
TEMPLATE = app


SOURCES += main.cpp\
        FenPrincipale.cpp \
    LoginDialog.cpp \
    aPropos.cpp \
    registerDialog.cpp

HEADERS  += FenPrincipale.h \
    LoginDialog.h \
    aPropos.h \
    registerDialog.h

FORMS    += FenPrincipale.ui \
    LoginDialog.ui \
    aPropos.ui \
    registerDialog.ui

RESOURCES += \
    img.qrc
