QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditcalc.cpp \
    depositcalc.cpp \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    qcustomplot.cpp \
    smartcalc.cpp \
    ../s21_smart_calc.c \
    ../s21_RPN.c \
    ../s21_calculate.c \
    ../s21_credit_calc.c \
    ../s21_parse_string.c \
    ../s21_stack.c \
    ../s21_deposit_calc.c \
    ../s21_validation.c



HEADERS += \
    creditcalc.h \
    depositcalc.h \
    mainwindow.h \
    ../s21_smart_calc.h \
    plot.h \
    qcustomplot.h \
    smartcalc.h

FORMS += \
    creditcalc.ui \
    depositcalc.ui \
    mainwindow.ui \
    plot.ui \
    smartcalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
