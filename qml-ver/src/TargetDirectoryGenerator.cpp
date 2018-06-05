#include "TargetDirectoryGenerator.hpp"

TargetDirectoryGenerator::TargetDirectoryGenerator(QObject* parent)
    : QObject(parent)
{
    connect(this, &TargetDirectoryGenerator::currentDirectoryChanged, this,
            &TargetDirectoryGenerator::onCurrentDirectoryChanged);
}

QString TargetDirectoryGenerator::currentDirectory() const
{
    return m_currentDirectory;
}

void TargetDirectoryGenerator::setCurrentDirectory(QString currentDirectory)
{
    if (m_currentDirectory == currentDirectory)
        return;
    m_currentDirectory = currentDirectory;
    emit currentDirectoryChanged();
}

QString TargetDirectoryGenerator::targetDirectory() const
{
    return m_targetDirectory;
}

void TargetDirectoryGenerator::setTargetDirectory(QString targetDirectory)
{
    if (m_targetDirectory == targetDirectory)
        return;
    m_targetDirectory = targetDirectory;
    emit targetDirectoryChanged();
}

void TargetDirectoryGenerator::onCurrentDirectoryChanged()
{
    m_targetDirectory = m_currentDirectory + "/selected/";
    emit targetDirectoryChanged();
}
