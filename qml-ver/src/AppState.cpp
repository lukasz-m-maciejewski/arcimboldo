#include "AppState.hpp"

#include <QDebug>
#include <QUrl>

AppStateAccess::AppStateAccess()
{
    connect(&AppState::Instance(), &AppState::currentDirectoryChanged,
            this, &AppStateAccess::currentDirectoryChanged);
}

QString AppStateAccess::currentDirectory() const
{
    return AppState::Instance().currentDirectory();
}

void AppStateAccess::setCurrentDirectory(QString currentDirectory)
{
    AppState::Instance().setCurrentDirectory(currentDirectory);
}


AppState::AppState()
{

}

AppState& AppState::Instance()
{
    static AppState state;
    return state;
}

QString AppState::currentDirectory() const
{
 return m_currentDirectory;
}

void AppState::setCurrentDirectory(QString currentDirectory)
{
    QUrl urlDir(currentDirectory);
    QString dirParsed;
    if (urlDir.isValid())
    {
        dirParsed = urlDir.path();
        qDebug() << "from url: " << dirParsed;
    }
    else
    {
        dirParsed = currentDirectory;
        qDebug() << "unchanged: " << dirParsed;
    }
    if (m_currentDirectory != dirParsed)
    {
        m_currentDirectory = dirParsed;
        emit currentDirectoryChanged();
    }
}
