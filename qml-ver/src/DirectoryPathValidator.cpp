#include "DirectoryPathValidator.hpp"

#include <QDebug>
#include <QFileInfo>

DirectoryPathValidator::DirectoryPathValidator()
{
}

QValidator::State DirectoryPathValidator::validate(QString& pathToDir,
                                                   int&) const
{
    QFileInfo dirInfo{pathToDir};
    if (dirInfo.isDir())
    {
        qDebug() << "query with: " << pathToDir << ";; accepted";
        return State::Acceptable;
    }
    else
    {
        qDebug() << "query with: " << pathToDir;
        return State::Intermediate;
    }
}
