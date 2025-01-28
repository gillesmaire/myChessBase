QT       += core gui sql concurrent 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += CHESS_NO_EXCEPTIONS

SOURCES += \
    calendardialog.cpp \
    checkboxdelegate.cpp \
    chesboardcursor.cpp \
    chessboard.cpp \
    chessstackedwidget.cpp \
    colorbutton.cpp \
    creationbase.cpp \
    customsqlcolumnproxymodel.cpp \
    dialogprogressbarimport.cpp \
    dialogshortcuts.cpp \
    ecotablegeneration.cpp \
    filledspinbox.cpp \
    formconfig.cpp \
    formnavigationbutton.cpp \
    formpgneditor.cpp \
    formtitle.cpp \
    formuniversmypreferences.cpp \
    limitedtextedit.cpp \
    main.cpp \
    mainwindow.cpp \
    movablePiece.cpp \
    mytableview.cpp \
    nag.cpp \
    readpgn.cpp \
    universpgn.cpp \
    utils.cpp

HEADERS += \
    BooleanCheckBoxDelegate.h \
    calendardialog.h \
    checkboxdelegate.h \
    chesboardcursor.h \
    chessboard.h \
    chessstackedwidget.h \
    colorbutton.h \
    creationbase.h \
    customsqlcolumnproxymodel.h \
    dialogprogressbarimport.h \
    dialogshortcuts.h \
    ecotablegeneration.h \
    filledspinbox.h \
    formconfig.h \
    formnavigationbutton.h \
    formpgneditor.h \
    formtitle.h \
    formuniversmypreferences.h \
    limitedtextedit.h \
    mainwindow.h \
    movablePiece.h \
    mytableview.h \
    nag.h \
    readpgn.h \
    universpgn.h \
    utils.h

FORMS += \
    dialogprogressbarimport.ui \
    dialogshortcuts.ui \
    formconfig.ui \
    formnavigationbutton.ui \
    formpgneditor.ui \
    formtitle.ui \
    formuniversmypreferences.ui \
    mainwindow.ui \
    universpgn.ui

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
    System/ToDo.md \
    System/cursor.png
