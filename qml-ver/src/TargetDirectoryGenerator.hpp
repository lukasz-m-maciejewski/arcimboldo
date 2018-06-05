#ifndef TARGETDIRECTORYGENERATOR_HPP
#define TARGETDIRECTORYGENERATOR_HPP

#include <QObject>

class TargetDirectoryGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE
                   setCurrentDirectory NOTIFY currentDirectoryChanged)
    Q_PROPERTY(QString targetDirectory READ targetDirectory WRITE
                   setTargetDirectory NOTIFY targetDirectoryChanged)
public:
    explicit TargetDirectoryGenerator(QObject* parent = nullptr);

    QString currentDirectory() const;
    void setCurrentDirectory(QString);

    QString targetDirectory() const;
    void setTargetDirectory(QString);

signals:
    void currentDirectoryChanged();
    void targetDirectoryChanged();

public slots:
    void onCurrentDirectoryChanged();


private:
    QString m_currentDirectory;
    QString m_targetDirectory;
};

#endif // TARGETDIRECTORYGENERATOR_HPP
