QT       += core gui sql concurrent svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += CHESS_NO_EXCEPTIONS

SOURCES += \
    chessboard.cpp \
    chessstackedwidget.cpp \
    colorbutton.cpp \
    creationbase.cpp \
    dialogabout.cpp \
    dialoginfo.cpp \
    dialogprogressbarimport.cpp \
    dialogconfiguration.cpp \
    dialogshortcuts.cpp \
    ecotablegeneration.cpp \
    formcreatepgn.cpp \
    main.cpp \
    mainwindow.cpp \
    myvisitor.cpp \
    piece.cpp \
    utils.cpp

HEADERS += \
    chessboard.h \
    chessstackedwidget.h \
    colorbutton.h \
    creationbase.h \
    dialogabout.h \
    dialoginfo.h \
    dialogprogressbarimport.h \
    dialogconfiguration.h \
    dialogshortcuts.h \
    ecotablegeneration.h \
    formcreatepgn.h \
    mainwindow.h \
    myvisitor.h \
    piece.h \
    utils.h

FORMS += \
    dialogabout.ui \
    dialoginfo.ui \
    dialogprogressbarimport.ui \
    dialogconfiguration.ui \
    dialogshortcuts.ui \
    formcreatepgn.ui \
    mainwindow.ui

TRANSLATIONS += \
    myChessBase_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

INCLUDEPATH += ./chess-library/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    System.qrc \
    Fonts.qrc
