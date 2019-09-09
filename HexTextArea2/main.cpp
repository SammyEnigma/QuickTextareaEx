#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#ifdef Q_OS_WIN // for homedirpath reading from registry
#  include <qt_windows.h>
#  ifndef Q_OS_WINRT
#    include <shlobj.h>
#  endif
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.addImportPath("F:/C++/Crypto/HexTextArea2/libs");
    for(QString path : engine.importPathList())
        qDebug() << path;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
