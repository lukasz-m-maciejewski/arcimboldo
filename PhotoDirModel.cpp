#include "PhotoDirModel.hpp"
#include <QDebug>
#include <QDir>
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
    switch(role)
    {
    case FilepathRole:
        return getFilepathAt(static_cast<std::size_t>(index.row()));
    case FilenameRole:
        return getFilenameAt(static_cast<std::size_t>(index.row()));
    case SelectedRole:
        return isSelected(static_cast<std::size_t>(index.row()));
    default:
        qDebug() << "!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!";
        return {};

    }
}

QHash<int, QByteArray> PhotoDirModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FilepathRole] = "filepath";
    names[FilenameRole] = "filename";
    names[SelectedRole] = "selected";
    return names;
}

bool PhotoDirModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    qDebug() << "index:" << index << " value:" << value << " role:" << role;
    if (role == SelectedRole)
    {
        m_directoryEntries.at(static_cast<std::size_t>(index.row())).selected = value.toBool();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void PhotoDirModel::emitCurrentSelection()
{
    qDebug() << "ding current:" << m_currentDirectory;
    QString current = m_currentDirectory.mid(7, m_currentDirectory.size() - 7);
    qDebug() << "ding current:" << current;
    QDir workdir{current};
    auto rv = workdir.mkdir("./selection");
    qDebug() << "mkdir returned " << rv;

    for (const auto& elem : m_directoryEntries)
    {
        if (elem.selected)
        {
            QFile cf{QString::fromStdString(elem.path.string())};
            QString newPath = QString::fromStdString(elem.path.parent_path().string()) + "/selection/" + QString::fromStdString(elem.path.filename());
            auto cpRv = cf.copy(newPath);
            qDebug() << "copy of " << cf.fileName() << " yelds " << cpRv;
        }
    }
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
    qDebug() << __FUNCTION__ << ":" << __LINE__ << filepath.c_str();
    return QString::fromStdString(filepath);
}

bool PhotoDirModel::isSelected(std::size_t pos) const
{
    return m_directoryEntries.at(pos).selected;
}
