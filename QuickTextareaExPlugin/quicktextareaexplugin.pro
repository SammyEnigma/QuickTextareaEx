TEMPLATE = lib
TARGET = quicktextareaexplugin
QT += qml quick
CONFIG += plugin c++11
QT_PRIVATE += quick-private
QT_PRIVATE += quicktemplates2-private

TARGET = $$qtLibraryTarget($$TARGET)
uri = QuickTextAreaEx
message($$TARGET)
# Input
SOURCES += \
        quicktextareaexplugin_plugin.cpp \
        quicktextareaex.cpp

HEADERS += \
        quicktextareaexplugin_plugin.h \
        quicktextareaex.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
CONFIG -= qml_debug
