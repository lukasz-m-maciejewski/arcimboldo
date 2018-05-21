#include "PhotoDirModel.hpp"
#include <QDebug>
#include <set>

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
    //auto end = static_cast<int>(m_directoryEntries.size());
    //emit dataChanged(index(0), index(end));
    emit layoutChanged();
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
        qDebug() << "!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!11";
        return {};
    }
    else if (role == FilepathRole)
    {
        return getFilepathAt(static_cast<std::size_t>(index.row()));
    }
    else if (role == FilenameRole)
    {
        return getFilenameAt(static_cast<std::size_t>(index.row()));
    }
    else if (role == SelectedRole)
    {
        return isSelected(static_cast<std::size_t>(index.row()));
    }
    else
        return {};
}

QHash<int, QByteArray> PhotoDirModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FilepathRole] = "filepath";
    names[FilenameRole] = "filename";
    names[SelectedRole] = "selected";
    return names;
}

bool PhotoDirModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "index:" << index << " value:" << value << " role:" << role;
    return false;
}

void PhotoDirModel::populateDirectoryEntries()
{
    const std::set<fs::path> image_file_exts = {".jpeg", ".jpg"};
    m_directoryEntries.clear();

    qDebug() << "m_currentDirectory.toStdString():" << m_currentDirectory;

    fs::path dir = m_currentDirectory.toStdString().substr(7);

    qDebug() << "path:" << dir.string().c_str();

    for (auto& entry : fs::directory_iterator(dir))
    {
        qDebug() << "entry:" << entry.path().string().c_str();
        if (entry.is_regular_file() and (image_file_exts.count(entry.path().extension()) > 0))
        {
            m_directoryEntries.emplace_back(entry.path());
        }
    }
    qDebug() << "m_directoryEntries.size():" << m_directoryEntries.size();
}

QString PhotoDirModel::getFilenameAt(std::size_t pos) const
{
    std::string filename = m_directoryEntries.at(pos).path.filename().string();
    qDebug() << __FUNCTION__ << filename.c_str();
    return QString::fromStdString(filename);
}

QString PhotoDirModel::getFilepathAt(std::size_t pos) const
{
    std::string filepath = m_directoryEntries.at(pos).path.string();
    qDebug() << __FUNCTION__ << filepath.c_str();
    return QString::fromStdString(filepath);
}

bool PhotoDirModel::isSelected(std::size_t pos) const
{
    return m_directoryEntries.at(pos).selected;
}
