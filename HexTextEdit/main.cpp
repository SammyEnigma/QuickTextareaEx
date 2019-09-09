#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "quicktexteditex.h"
#include "quicktextareaex.h"
#include "quicktextareasub.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //qmlRegisterType<QuickTextEditEx,1>("qtproject.extern", 1, 1, "TextEditEx");
    qmlRegisterType<QQuickTextEdit,7>("qtproject.extern", 1, 1, "QTextEdit");
    qmlRegisterType<QQuickTextArea,7>("qtproject.extern", 1, 1, "QTextArea");
    qmlRegisterType<QuickTextAreaEx,7>("qtproject.extern", 1, 1, "TextAreaEx");
    //qmlRegisterType<QuickTextAreaSub,1>("qtproject.extern", 1, 1, "TextAreaExSub");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
