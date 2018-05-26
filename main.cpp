#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>

#include "PhotoDirModel.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("graycatworkshop");
    QCoreApplication::setOrganizationDomain("graycatworkshop.com");
    QCoreApplication::setApplicationName("Photo Selector");

    QSettings settings;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<PhotoDirModel>("com.graycatworkshop.photoselector", 1, 0, "PhotoDirModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
