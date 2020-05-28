#pragma once

#include <QObject>
#include <QScopedPointer>

#include "ft_lib_global.h"

namespace FT {
namespace controllers {

class FT_LIB_EXPORT AccountController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AccountController)
    Q_PROPERTY(QString ui_login READ login WRITE updateLogin NOTIFY loginChanged)
    Q_PROPERTY(QString ui_email READ email WRITE updateEmail NOTIFY emailChanged)
    Q_PROPERTY(QString ui_password READ password WRITE updatePassword NOTIFY passwordChanged)

public:
    explicit AccountController(QObject *parent = nullptr);
    virtual ~AccountController() override;

    bool loadAccountData(const QString& login, const QString& password);

    QString login() const;
    QString email() const;
    QString password() const;

    bool updateLogin(const QString& login);
    bool updateEmail(const QString& email);
    bool updatePassword(const QString& password);

signals:
    void loginChanged(const QString& newl, const QString& oldl);
    void emailChanged(const QString& newe, const QString& olde);
    void passwordChanged(const QString& newp, const QString& oldp);

private:

    class Implementation;
    QScopedPointer<Implementation> impl;

};

} //controllers
} //FT



