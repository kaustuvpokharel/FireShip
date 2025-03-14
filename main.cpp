#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Controller.h>
#include "QObject"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Controller control(&engine);
    engine.rootContext()->setContextProperty("control", &control);

    const QUrl url(u"qrc:/untitled3/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
