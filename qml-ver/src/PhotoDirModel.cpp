#include "PhotoDirModel.hpp"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <set>
#include <QSettings>
#include <QStandardPaths>

PhotoDirModel::PhotoDirModel(QObject* parent)
    : QAbstractListModel{parent}, m_currentDirectory{}, m_directoryEntries{}
{
    auto picList = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    if (picList.size() > 0)
    {
        m_currentDirectory = picList[0];
        populateDirectoryEntries();

        emit layoutChanged();
        emit currentDirectoryChanged();
    }
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

QString PhotoDirModel::targetDirectory() const
{
    return m_targetDirectory;
}

void PhotoDirModel::setTargetDirectory(QString s)
{
    if (m_targetDirectory == s)
        return;

    m_targetDirectory = s;
    emit targetDirectoryChanged();
}

int PhotoDirModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_directoryEntries.size());
}

QVariant PhotoDirModel::data(const QModelIndex& index, int role) const
{
    qDebug() << "index:" << index << " role:" << role;
    switch (role)
    {
    case FilepathRole: return getFilepathAt(index.row());
    case FilenameRole: return getFilenameAt(index.row());
    case SelectedRole: return isSelected(index.row());
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

bool PhotoDirModel::setData(const QModelIndex& index, const QVariant& value,
                            int role)
{
    qDebug() << "index:" << index << " value:" << value << " role:" << role;
    if (role == SelectedRole)
    {
        m_directoryEntries[index.row()].selected = value.toBool();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void PhotoDirModel::emitCurrentSelection()
{
    constexpr auto new_dir_rel = "/selection/";
    qDebug() << "ding current:" << m_currentDirectory;
    QString current = [](QString& qs)
    {
        if (qs.left(5) == "file:")
        {
            return qs.mid(7);
        }
        else
        {
            return qs;
        }
    }(m_currentDirectory);

    QDir workdir{current};
    auto rv = workdir.mkdir("./selection");
    qDebug() << "mkdir returned " << rv;

    for (const auto& elem : m_directoryEntries)
    {
        if (elem.selected)
        {
            QFile cf{elem.fileinfo.filePath()};
            QString newPath = elem.fileinfo.dir().path() + new_dir_rel +
                              elem.fileinfo.fileName();
            qDebug() << "new path:" << newPath;
            auto cpRv = cf.copy(newPath);
            qDebug() << "copy of " << cf.fileName() << " yields " << cpRv;
        }
    }
}

void PhotoDirModel::populateDirectoryEntries()
{
    const std::set<QString> image_file_exts = {".jpeg", ".jpg"};
    m_directoryEntries.clear();

    qDebug() << "m_currentDirectory.toStdString():" << m_currentDirectory;

    auto dir = [](QString& qs)
    {
        if (qs.left(5) == "file:")
        {
            return qs.mid(7);
        }
        else
        {
            return qs;
        }
    }(m_currentDirectory);

    qDebug() << "path:" << dir;

    auto dirIter = QDirIterator{dir};

    while (dirIter.hasNext())
    {
        QString filename = dirIter.next();
        qDebug() << "next: " << filename;
        QFileInfo fileinfo{filename};
        if (fileinfo.isFile())
        {
            m_directoryEntries.push_back(fileinfo);
        }
    }
    qDebug() << "m_directoryEntries.size():" << m_directoryEntries.size();
}

QString PhotoDirModel::getFilenameAt(size_type pos) const
{
    return m_directoryEntries[pos].fileinfo.fileName();
}

QString PhotoDirModel::getFilepathAt(size_type pos) const
{
    return m_directoryEntries[pos].fileinfo.filePath();
}

bool PhotoDirModel::isSelected(size_type pos) const
{
    return m_directoryEntries.at(pos).selected;
}
