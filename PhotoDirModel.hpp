#ifndef PHOTODIRMODEL_HPP
#define PHOTODIRMODEL_HPP

#include <QAbstractListModel>

#include <QFileInfo>
#include <string>
#include <vector>

struct Entry
{
    Entry() : fileinfo{""}, selected{false}
    {
    }
    Entry(QString p) : fileinfo{p}, selected{false}
    {
    }
    Entry(QFileInfo fi) : fileinfo{std::move(fi)}, selected{false}
    {
    }
    QFileInfo fileinfo;
    bool selected;
};

class PhotoDirModel : public QAbstractListModel
{
    using size_type = QVector<Entry>::size_type;
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE
                   setCurrentDirectory NOTIFY currentDirectoryChanged)

    static constexpr auto FilepathRole = Qt::UserRole;
    static constexpr auto FilenameRole = Qt::UserRole + 1;
    static constexpr auto SelectedRole = Qt::UserRole + 2;

public:
    PhotoDirModel(QObject* parent = nullptr);

    QString currentDirectory() const;
    void setCurrentDirectory(QString);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value,
                 int role = Qt::EditRole) override;

signals:
    void currentDirectoryChanged();

public slots:
    void emitCurrentSelection();

private:
    void populateDirectoryEntries();

    QString getFilenameAt(size_type) const;
    QString getFilepathAt(size_type) const;
    bool isSelected(size_type) const;

    QString m_currentDirectory;

    QVector<Entry> m_directoryEntries;
};

#endif // PHOTODIRMODEL_HPP
