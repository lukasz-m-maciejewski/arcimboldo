#ifndef APPSTATE_HPP
#define APPSTATE_HPP

#include <QObject>

class AppStateAccess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE
                   setCurrentDirectory NOTIFY currentDirectoryChanged)

public:
    AppStateAccess();

    QString currentDirectory() const;
    void setCurrentDirectory(QString);

signals:
    void currentDirectoryChanged();
};

class AppState : public QObject
{
private:

    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE
                   setCurrentDirectory NOTIFY currentDirectoryChanged)

    AppState();

public:
    static AppState& Instance();

public:
    QString currentDirectory() const;
    void setCurrentDirectory(QString);

signals:
    void currentDirectoryChanged();

private:
    QString m_currentDirectory;

};

#endif // APPSTATE_HPP
