#include "PhotoDirModel.hpp"
#include <QDebug>
#include <filesystem>

namespace fs = std::filesystem;

PhotoDirModel::PhotoDirModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_currentDirectory{}
    , m_directoryEntries{}
{

}

QString PhotoDirModel::currentDirectory() const
{
    return m_currentDirectory;
}

void PhotoDirModel::setCurrentDirectory(QString currentDirectory)
{
    qDebug("aaa");
    if (m_currentDirectory == currentDirectory)
        return;

    m_currentDirectory = currentDirectory;

    populateDirectoryEntries();
    emit currentDirectoryChanged();
}

int PhotoDirModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_directoryEntries.size());
}

QVariant PhotoDirModel::data(const QModelIndex& index, int role) const
{
    qDebug() << "index:" << index << " role:" << role;
    if (role < Qt::UserRole)
    {
        qDebug() << "AAAAAA";
        return {};
    }
    else if (role == Qt::UserRole)
        return QString::fromStdString(m_directoryEntries.at(static_cast<std::size_t>(index.row())));
    else
        return {};
}

QHash<int, QByteArray> PhotoDirModel::roleNames() const
{
    qDebug() << "AAAAAA";
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "filename";
    return names;
}

void PhotoDirModel::populateDirectoryEntries()
{
    m_directoryEntries.clear();

    qDebug() << "m_currentDirectory.toStdString():" << m_currentDirectory;

    for (auto& entry : fs::directory_iterator(m_currentDirectory.toStdString().substr(7)))
    {
        if (entry.is_regular_file())
            m_directoryEntries.push_back(entry.path().filename());
    }
}
