QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = UniversityLMS
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    LoginDialog.cpp \
    AdminWindow.cpp \
    InstructorWindow.cpp \
    StudentWindow.cpp

HEADERS += \
    MainWindow.h \
    LoginDialog.h \
    AdminWindow.h \
    InstructorWindow.h \
    StudentWindow.h \
    User.h \
    Admin.h \
    Instructor.h \
    Student.h \
    Course.h \
    Assignment.h \
    Attendance.h \
    FeeChallan.h \
    Dashboard.h \
    Date.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
