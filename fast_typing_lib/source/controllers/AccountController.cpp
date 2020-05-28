
#include "AccountController.hpp"

#include <QDebug>

#include "DatabaseModel.hpp"


namespace FT {
namespace controllers {


class AccountController::Implementation
{
public:
    Implementation(AccountController* obj): parent(obj) { }

    AccountController* parent;

    QString login{""};
    QString email{""};
    QString password{""};

    int accountId{-1};

    bool accountExists(const QString& login, const QString& password) const {
        QString query = QString("SELECT id FROM Account "
                                     "WHERE Account.login = \"%1\" "
                                     "AND Account.password = \"%2\"").arg(login).arg(password);
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        return !list.isEmpty();
    }

};

AccountController::AccountController(QObject* parent): QObject(parent) {
    impl.reset(new Implementation(this));
}

AccountController::~AccountController() { }

bool AccountController::loadAccountData(const QString& login, const QString& password) {
    if (!impl->accountExists(login, password))
        return false;
    QString query = QString("SELECT id, email FROM Account "
                                 "WHERE Account.login = \"%1\" "
                                 "AND Account.password = \"%2\"").arg(login).arg(password);

    auto list = data::DatabaseModel::instance().selectRows(query).value();
    if (list[0].isEmpty()) {
        qDebug() << "incorrect login or password";
        return false;
    }

    impl->accountId = qvariant_cast<int>(list[0][0]);
    impl->email = qvariant_cast<QString>(list[0][1]);
    impl->login = login;
    impl->password = password;
    qDebug() << impl->accountId << ' '
             << impl->login << ' '
             << impl->email << ' '
             << password;

    return true;
}

QString AccountController::login() const {
    return impl->login;
}

QString AccountController::email() const {
    return impl->email;
}

QString AccountController::password() const {
    return impl->password;
}

void AccountController::updateLogin(const QString& login) {
    if (login == impl->login)
        return;
    QString statement = "UPDATE login = :login WHERE id = :id";
    QVariantMap map{{":login", login}, {":id", impl->accountId}};
    data::DatabaseModel::instance().updateRow(statement, map);
    QString temp = std::move(impl->login);
    impl->login = login;
    emit loginChanged(login, temp);
}

void AccountController::updateEmail(const QString& email) {
    if (email == impl->email)
        return;
    QString statement = "UPDATE email = :email WHERE id = :id";
    QVariantMap map{{":email", email}, {":id", impl->accountId}};
    data::DatabaseModel::instance().updateRow(statement, map);
    QString temp = std::move(impl->email);
    impl->email = email;
    emit emailChanged(email, temp);
}

void AccountController::updatePassword(const QString& password) {
    if (password == impl->password)
        return;
    QString statement = "UPDATE password = :password WHERE id = :id";
    QVariantMap map{{":password", password}, {":id", impl->accountId}};
    data::DatabaseModel::instance().updateRow(statement, map);
    QString temp = std::move(impl->password);
    impl->password = password;
    emit loginChanged(password, temp);
}


} //controllers
} //FT


