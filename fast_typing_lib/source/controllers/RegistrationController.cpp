

#include "RegistrationController.hpp"

#include <QDate>
#include <QDebug>

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

    QString currentDate = QDate::currentDate().toString(Qt::DateFormat::ISODate);

    bool created = createAccountRecord(login, email, password, currentDate);

    if (!created) {
        qDebug() << "unable to create Account with data: \n\t"
                 << login << "\n\t" << email << "\n\t" << password;
        return -1;
    }

    QString selectId = QString("SELECT id FROM Account WHERE login = \"%1\"").arg(login);
    int id = data::DatabaseModel::instance().selectRows(selectId).value()[0][0].toInt();
    qDebug() << id;

    created = createAccountSettingsRecord(id);

    if (!created) {
        qDebug() << "unable to create AccountSettings with data: \n\t"
                 << login << "\n\t" << email << "\n\t" << password;
        return -1;
    }

    created = createAccountStatisticsRecord(id);

    if (!created) {
        qDebug() << "unable to create AccountStatistics with data: \n\t"
                 << login << "\n\t" << email << "\n\t" << password;
        return -1;
    }


    return id;
}

bool RegistrationController::createAccountRecord(const QString& login, const QString& email, const QString& password, const QString& currentDate) const {

    QString statement = QString("INSERT INTO Account (login, email, password, created_at)"
                                " VALUES ('%1', '%2', '%3', '%4')").
                                arg(login).arg(email).arg(password).arg(currentDate);

    bool created = data::DatabaseModel::instance().insertRow(statement);
    return created;
}

bool RegistrationController::createAccountSettingsRecord(int id) const {
    QString statement = QString("INSERT INTO AccountSettings (user_id, keyboard_layout_id, operating_system_id, "
                                   "general_settings_id, keyboard_settings_id) VALUES(%1, 1, 1, 0, 0)").arg(id);
    bool created = data::DatabaseModel::instance().insertRow(statement);
    return created;
}

bool RegistrationController::createAccountStatisticsRecord(int id)  const {
    QString statement = QString("INSERT INTO AccountStatistics (user_id, characters, significance, errors, time_spent)"
                                "VALUES(%1, 0, 0, 0, 0)").arg(id);
    bool created = data::DatabaseModel::instance().insertRow(statement);
    return created;
}

RegistrationController::RegistrationController(QObject* parent): QObject(parent) {
    impl.reset(new Implementation(this));
}

RegistrationController::~RegistrationController() { }


} //controllers
} //FT
