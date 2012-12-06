include(pcsp.pri)

CONFIG(debug, debug|release) {
    CONFIGNAME=debug
} else {
    CONFIGNAME=release
}

MOC_DIR = moc
UI_DIR = ui
OBJECTS_DIR = $$CONFIGNAME/obj
DESTDIR = $$CONFIGNAME

INCLUDEPATH += \
    ../../3rdparty/glee \
    ../../3rdparty/portaudio/include \
    ../../pcsp/src \
    ../../pcsp/src/hle \
    ../../pcsp/src/common \
    ../../pcsp/src/qt4 \
    ../../pcsp/src/debugger/qt4
DEFINES += HAVE_SETJMP_H \
    GCC_HASCLASSVISIBILITY \
    HAVE_SIGALTSTACK \
    HAVE_X11 \
    QT_THREAD_SUPPORT \
    QT_CORE_LIB

QMAKE_CXXFLAGS += -Wno-unused-parameter \
    -Wno-return-type \
    -msse -msse2
QMAKE_CXXFLAGS += -fno-strict-aliasing

unix {
    # All Unix
    LIBS += -lz -lportaudio
}
unix:!macx {
    # Linux only
    LIBS += -lrt
}
macx {
    # Mac OSX only
    LIBS += \
        -framework CoreFoundation \
        -framework QtOpenGL \
        -framework QtXml
}

PRECOMPILED_HEADER = ../src/stdafx.h

OTHER_FILES += pcsp/Resources/video48x48.png \
    pcsp/Resources/umd.png \
    pcsp/Resources/StepOverIcon.png \
    pcsp/Resources/StepOutIcon.png \
    pcsp/Resources/StepIntoIcon.png \
    pcsp/Resources/sound48x48.png \
    pcsp/Resources/reset.png \
    pcsp/Resources/quit.png \
    pcsp/Resources/psp.png \
    pcsp/Resources/PlayIcon.png \
    pcsp/Resources/play.png \
    pcsp/Resources/pic1.png \
    pcsp/Resources/pcsplogo.png \
    pcsp/Resources/pcsp.ico \
    pcsp/Resources/PauseIcon.png \
    pcsp/Resources/pause.png \
    pcsp/Resources/open_file.png \
    pcsp/Resources/memorycard.png \
    pcsp/Resources/memcard48x48.png \
    pcsp/Resources/icon0.png \
    pcsp/Resources/controls.png \
    pcsp/src/SConscript \
    pcsp/src/al/al.def
QT += opengl xml
