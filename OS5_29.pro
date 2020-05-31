QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BIOS.cpp \
    Cl_ASCII.cpp \
    Cl_Byte.cpp \
    Cl_RAM.cpp \
    Cl_ROM.cpp \
    F_code_library.cpp \
    File.cpp \
    Process_RAM.cpp \
    Rom_system.cpp \
    TestExceptionSystem.cpp \
    clock.cpp \
    controller.cpp \
    file_widget.cpp \
    global.cpp \
    login_page.cpp \
    login_system.cpp \
    main.cpp \
    mainwindow.cpp \
    snake_widget.cpp \
    taskcontroller.cpp \
    texteditor.cpp

HEADERS += \
    BIOS.h \
    Cl_ASCII.h \
    Cl_Byte.h \
    Cl_RAM.h \
    Cl_ROM.h \
    ExceptionSystem.h \
    F_code_library.h \
    File.h \
    Header.h \
    Process_RAM.h \
    Rom_system.h \
    clock.h \
    controller.h \
    file_widget.h \
    global.h \
    login_page.h \
    login_system.h \
    mainwindow.h \
    measure_time.h \
    snake_widget.h \
    taskcontroller.h \
    text_editor.h \
    texteditor.h

FORMS += \
    controller.ui \
    file_widget.ui \
    login_page.ui \
    mainwindow.ui \
    texteditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    osPractice2.pro

RESOURCES += \
    Resource.qrc

DISTFILES += \
    OS5_29.pro.user
