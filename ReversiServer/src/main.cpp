#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "reversiserver.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    // Create reversi server
    ReversiServer server;
    server.initialized();
    if (!server.startServer())
        return 125;

    // Create engine
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("ReversiServer", &server);

    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
