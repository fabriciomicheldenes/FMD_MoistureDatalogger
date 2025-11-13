QT += widgets serialport
requires(qtConfig(combobox))

TARGET = TerraMoistLogger
TEMPLATE = app

SOURCES += \
    main.cpp \
    src/QSerialPortInfoOperatores.cpp \
    src/consolemanager.cpp \
    src/mainwindow.cpp \
    src/settingsdialog.cpp \
    src/console.cpp

HEADERS += \
    include/QSerialPortInfoOperatores.h \
    include/consolemanager.h \
    include/mainwindow.h \
    include/settingsdialog.h \
    include/console.h

FORMS += \
    ui/mainwindow.ui \
    ui/settingsdialog.ui

RESOURCES += \
    TerraMoistLogger.qrc

RC_ICONS = images/app.ico

#CONFIG += console

target.path = ./build
INSTALLS += target
