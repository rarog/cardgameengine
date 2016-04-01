#-------------------------------------------------
#
# Project created by QtCreator 2011-08-20T11:50:51
#
#-------------------------------------------------

QT       += core gui
QT       += script scripttools svg

TARGET = CardGame
TEMPLATE = app

include( cardgameengine.pri )

SOURCES += main.cpp\
        Dialog.cpp \
    CardGame.cpp \
    LocalPlayer/LocalPlayer.cpp \
    LocalPlayer/LocalPlayground.cpp \
    GameLogics/ScriptedGameLogic.cpp \
    Cards/CardsModel.cpp \
    Cards/Card.cpp \
    Cards/CardStack.cpp \
    GameStatus.cpp \
    LocalPlayer/LocalView.cpp \
    LocalPlayer/LocalInteractivePlayground.cpp \
    Player.cpp \
    MainWindow.cpp \
    SettingDialog.cpp \
    LocalPlayer/AnimatedGraphicsScene.cpp \
    GameLogics/ScriptGameInterface.cpp \
    AboutDialog.cpp \
    Settings/ImageChooserWidget.cpp \
    LocalPlayer/CardFactory.cpp \
    GameLogicKatalog.cpp \
    Settings/SearchPathSettings.cpp \
    LocalPlayer/Utils/DirtEffect.cpp \
    Utils/WinDialog.cpp

HEADERS  += Dialog.h \
    CardGame.h \
    GameLogic.h \
    Player.h \
    LocalPlayer/LocalPlayer.h \
    LocalPlayer/LocalPlayground.h \
    GameLogics/ScriptedGameLogic.h \
    Cards/CardsModel.h \
    Cards/Card.h \
    Cards/CardStack.h \
    GameStatus.h \
    LocalPlayer/LocalView.h \
    LocalPlayer/LocalInteractivePlayground.h \
    Cards/Rank.h \
    Cards/Suit.h \
    MainWindow.h \
    SettingDialog.h \
    Cards/SelectionMode.h \
    LocalPlayer/AnimatedGraphicsScene.h \
    GameLogics/ScriptGameInterface.h \
    AboutDialog.h \
    Settings/ImageChooserWidget.h \
    LocalPlayer/CardFactory.h \
    Settings/SettingsItem.h \
    GameLogicKatalog.h \
    Settings/SearchPathSettings.h \
    LocalPlayer/Utils/DirtEffect.h \
    Utils/WinDialog.h

FORMS    += Dialog.ui \
    MainWindow.ui \
    AboutDialog.ui \
    Settings/SearchPathSettings.ui \
    SettingDialog.ui \
    Utils/WinDialog.ui

RESOURCES += \
    ScriptedGameLogics.qrc \
    CardDecks.qrc \
    images.qrc
