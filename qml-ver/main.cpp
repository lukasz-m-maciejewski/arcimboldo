#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>

#include "PhotoDirModel.hpp"

// todo list:
// TODO: export dir as global property
// TODO: decent style for list items
// TODO: highlight active item on the list
// TODO: set initial active item when loading new directory
// TODO: display current directory next to the button
// TODO: handle drag'n'drop for photos
// TODO: robust filtering of image/non-image files
// TODO: write customized folder selection dialog to work around the issues with the current one

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName("graycatworkshop");
    QCoreApplication::setOrganizationDomain("graycatworkshop.com");
    QCoreApplication::setApplicationName("Arcimboldo");

    QSettings settings;
    settings.setValue(
        DefaultLocationKey,
        QStandardPaths::standardLocations(QStandardPaths::PicturesLocation));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterType<PhotoDirModel>("com.graycatworkshop.Arcimboldo", 1, 0,
                                   "PhotoDirModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
