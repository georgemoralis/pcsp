######################################################################
# Automatically generated by qmake (2.01a) sam. nov. 20 22:34:29 2010
######################################################################

TEMPLATE = app
TARGET = pcsp-udb
DEPENDPATH += . qt4
INCLUDEPATH += . qt4
QT += sql

# Input
HEADERS += iso.h \
           isodrv.h \
           isolib.h \
           loaders.h \
           psf.h \
           types.h \
           umdimageloader.h \
           version.h \
           qt4/compatibilitydialog.h \
           qt4/customfilterproxymodel.h \
           qt4/ProgressCtrl.h \
           qt4/qpcspxmb.h \
           qt4/qumdmodel.h \
           qt4/sqlconnection.h
FORMS += qt4/compatibilitydialog.ui qt4/qpcspxmb.ui
SOURCES += iso.cpp \
           isodrv.cpp \
           loaders.cpp \
           main.cpp \
           psf.cpp \
           umdimageloader.cpp \
           qt4/compatibilitydialog.cpp \
           qt4/customfilterproxymodel.cpp \
           qt4/ProgressCtrl.cpp \
           qt4/qpcspxmb.cpp
RESOURCES += qt4/qpcspxmb.qrc