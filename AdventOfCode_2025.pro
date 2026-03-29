QT = core

CONFIG += c++17 cmdline

SOURCES += \
        day1.cpp \
        day10.cpp \
        day10_2.cpp \
        day11.cpp \
        day2.cpp \
        day2_2.cpp \
        day3.cpp \
        day3_2.cpp \
        day4.cpp \
        day4_2.cpp \
        day5.cpp \
        day5_2.cpp \
        day6.cpp \
        day6_2.cpp \
        day7.cpp \
        day7_2.cpp \
        day8.cpp \
        day9.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    day1.h \
    day10.h \
    day10_2.h \
    day11.h \
    day2.h \
    day2_2.h \
    day3.h \
    day3_2.h \
    day4.h \
    day4_2.h \
    day5.h \
    day5_2.h \
    day6.h \
    day6_2.h \
    day7.h \
    day7_2.h \
    day8.h \
    day9.h
