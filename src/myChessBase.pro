QT       += core gui sql concurrent 


system(/usr/local/bin/template.sh GPLV3.0 myChessBase https://github.com/gillesmaire/myChessBase.git)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -Wno-trigraphs
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += CHESS_NO_EXCEPTIONS

SOURCES += \
    calendardialog.cpp \
    chesboardcursor.cpp \
    chessboard.cpp \
    chessstackedwidget.cpp \
    colorbutton.cpp \
    dialogpromotion.cpp \
    dialogshortcuts.cpp \
    filledspinbox.cpp \
    formconfig.cpp \
    formnavigationbutton.cpp \
    formpgneditor.cpp \
    formresources.cpp \
    limitedtextedit.cpp \
    main.cpp \
    mainwindow.cpp \
    mytableview.cpp \
    myvisitor.cpp \
    nag.cpp \
    utils.cpp

HEADERS += \
    BooleanCheckBoxDelegate.h \
    calendardialog.h \
    chesboardcursor.h \
    chessboard.h \
    chessstackedwidget.h \
    colorbutton.h \
    dialogpromotion.h \
    dialogshortcuts.h \
    filledspinbox.h \
    formconfig.h \
    formnavigationbutton.h \
    formpgneditor.h \
    formresources.h \
    limitedtextedit.h \
    mainwindow.h \
    mytableview.h \
    myvisitor.h \
    nag.h \
    utils.h

FORMS += \
    dialogpromotion.ui \
    dialogshortcuts.ui \
    formconfig.ui \
    formnavigationbutton.ui \
    formpgneditor.ui \
    formresources.ui \
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

DISTFILES += \
    Ideas.md \
    System/Technicalnotes.md \
    System/ToDo.md \
    System/cursor.png
