#pragma once

#include <QObject>


namespace FT {
namespace controllers {


class RegistrationController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RegistrationController)
    Q_PROPERTY(int account_id READ accountId)
public:
    explicit RegistrationController(QObject *parent = nullptr);
    virtual ~RegistrationController() override;

    bool isLoginUnique(const QString& login) const;
    bool isEmailUnique(const QString& email) const;

    int accountId() const;

    int createAccount(const QString& login, const QString& email, const QString& password) const;
private:
    class Implementation;
    QScopedPointer<Implementation> impl;
};


} //controllers
} //FT


