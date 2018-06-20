#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QStandardPaths>

#include "AppState.hpp"
#include "DirectoryPathValidator.hpp"
#include "PhotoDirModel.hpp"
#include "TargetDirectoryGenerator.hpp"

// todo list:
// DONE: export dir as global property
// TODO: decent style for list items
// TODO: highlight active item on the list
// DONE: set initial active item when loading new directory
// DONE: display current directory next to the button
// TODO: handle drag'n'drop for photos
// TODO: robust filtering of image/non-image files
// TODO: write customized folder selection dialog to work around the issues with the current one
// TODO: save and restore last size and position in config
// TODO: save and restore last open dir

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
    qmlRegisterType<AppStateAccess>("com.graycatworkshop.Arcimboldo", 1, 0,
                                    "AppStateAccess");
    qmlRegisterType<DirectoryPathValidator>("com.graycatworkshop.Arcimboldo", 1,
                                            0, "DirectoryPathValidator");
    qmlRegisterType<TargetDirectoryGenerator>("com.graycatworkshop.Arcimboldo",
                                              1, 0, "TargetDirectoryGenerator");

    AppState::Instance().setCurrentDirectory(
        settings.value(DefaultLocationKey).toString());

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
