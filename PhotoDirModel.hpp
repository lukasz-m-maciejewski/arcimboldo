#ifndef PHOTODIRMODEL_HPP
#define PHOTODIRMODEL_HPP

#include <QAbstractListModel>

#include <vector>
#include <string>

class PhotoDirModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE setCurrentDirectory NOTIFY currentDirectoryChanged)

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

    QString m_currentDirectory;

    std::vector<std::string> m_directoryEntries;

};

#endif // PHOTODIRMODEL_HPP
