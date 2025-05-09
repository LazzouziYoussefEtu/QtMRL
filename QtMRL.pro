QT += charts widgets gui core openglwidgets opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000     # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/cpuusagechart.cpp \
    src/ramusagechart.cpp \
    src/wifisignalchart.cpp

HEADERS += \
    includes/cpuusagechart.h \
    includes/ramusagechart.h \
    includes/wifisignalchart.h

FORMS += \
    QtMRL.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
