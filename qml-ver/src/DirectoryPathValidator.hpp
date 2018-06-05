#ifndef DIRECTORYPATHVALIDATOR_HPP
#define DIRECTORYPATHVALIDATOR_HPP

#include <QValidator>

class DirectoryPathValidator : public QValidator
{
    Q_OBJECT
public:
    DirectoryPathValidator();

    State validate(QString&, int&) const override;

signals:

public slots:
};

#endif // DIRECTORYPATHVALIDATOR_HPP
