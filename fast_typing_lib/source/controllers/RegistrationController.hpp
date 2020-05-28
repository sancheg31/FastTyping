#pragma once

#include <QObject>

#include "ft_lib_global.h"

namespace FT {
namespace controllers {


class FT_LIB_EXPORT RegistrationController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RegistrationController)

public:
    explicit RegistrationController(QObject *parent = nullptr);
    virtual ~RegistrationController() override;

    bool isLoginUnique(const QString& login) const;
    bool isEmailUnique(const QString& email) const;

    int createAccount(const QString& login, const QString& email, const QString& password) const;
private:
    class Implementation;
    QScopedPointer<Implementation> impl;
};


} //controllers
} //FT


