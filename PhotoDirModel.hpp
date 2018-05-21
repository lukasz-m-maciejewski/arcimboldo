#ifndef PHOTODIRMODEL_HPP
#define PHOTODIRMODEL_HPP

#include <QAbstractListModel>

#include <vector>
#include <string>
#include <filesystem>

class PhotoDirModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE setCurrentDirectory NOTIFY currentDirectoryChanged)

    static constexpr auto FilepathRole = Qt::UserRole;
    static constexpr auto FilenameRole = Qt::UserRole + 1;

public:
    PhotoDirModel(QObject *parent = nullptr);

    QString currentDirectory() const;
    void setCurrentDirectory(QString);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void currentDirectoryChanged();

private:
    void populateDirectoryEntries();

    QString getFilenameAt(std::size_t) const;
    QString getFilepathAt(std::size_t) const;

    QString m_currentDirectory;

    std::vector<std::filesystem::path> m_directoryEntries;

};

#endif // PHOTODIRMODEL_HPP
