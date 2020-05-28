

#include "RegistrationController.hpp"

#include <QDate>

#include "DatabaseModel.hpp"


namespace FT {
namespace controllers {


class RegistrationController::Implementation
{
public:
    Implementation(RegistrationController* obj): parent(obj) { }

    RegistrationController* parent;
};

bool RegistrationController::isLoginUnique(const QString& login) const {
    QString statement = QString("SELECT login FROM Account WHERE login = \"%1\"").arg(login);
    auto list = data::DatabaseModel::instance().selectRows(statement).value();
    return list.isEmpty();
}

bool RegistrationController::isEmailUnique(const QString& email) const {
    QString statement = QString("SELECT email FROM Account WHERE email = \"%1\"").arg(email);
    auto list = data::DatabaseModel::instance().selectRows(statement).value();
    return list.isEmpty();
}

int RegistrationController::createAccount(const QString& login,
                                          const QString& email,
                                          const QString& password) const {

    QString statement = QString("INSERT INTO Account (login, email, password, created_at)"
                                " VALUES (:login, :email, :password, :created_at)");
    QVariantMap map{
                    {QString(":login"), login},
                    {QString(":email"), email},
                    {QString(":password"), password},
                    {QString(":created_at"), QDate::currentDate().toString(Qt::DateFormat::ISODate)}
                   };
    bool created = data::DatabaseModel::instance().insertRow(statement, map);
    if (!created)
        return -1;

    QString selectId = QString("SELECT id FROM Account WHERE login = \"%1\"").arg(login);
    auto list = data::DatabaseModel::instance().selectRows(selectId).value();
    return qvariant_cast<int>(list[0][0]);
}

RegistrationController::RegistrationController(QObject* parent): QObject(parent) {
    impl.reset(new Implementation(this));
}

RegistrationController::~RegistrationController() { }


} //controllers
} //FT
