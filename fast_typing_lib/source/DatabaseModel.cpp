
#include "DatabaseModel.hpp"

#include <QString>
#include <QVariant>
#include <QtSql>

#include <QDebug>

#include <algorithm>
#include <exception>

namespace FT {
namespace data {


class DatabaseModel::Implementation
{
public:
    Implementation() {
        database = QSqlDatabase::addDatabase(dbType, dbConnectionName);
        database.setDatabaseName(dbName);
        database.open();
        if (!database.isOpen())
            qDebug() << "database is not open";
    }

    ~Implementation() {
        database.close();
        QSqlDatabase::removeDatabase(dbConnectionName);
    }

    QSqlDatabase database;

    const char* dbConnectionName{"fast_typing_db"};
    const char* dbType{"QSQLITE"};
    const char* dbName{"DBFastTyping.db"};
    const char* dbUsername{"sancheg31"};
    const char* dbPassword{"Computer784"};

private:
    QString sqliteVersion() const {
        QSqlQuery query(database);
        query.exec("SELECT sqlite_version()");

        if(query.next())
            return qvariant_cast<QString>(query.value(0));

        return QString::number(-1);

    }
};

/*static*/ DatabaseModel::Implementation* DatabaseModel::impl{nullptr};

FT::data::DatabaseModel& FT::data::DatabaseModel::instance() {
    static DatabaseModel inst{};
    return inst;
}

std::optional<QList<QVariantList>> DatabaseModel::selectRows(const QString& statement) const {
    QSqlQuery query(impl->database);
    query.setForwardOnly(true);

    if (!query.prepare(statement) || !query.exec()) {
        qDebug() << "incorrect statement: " << statement;
        return {};
    }

    std::size_t colsCount = query.record().count();
    QList<QVariantList> result{};

    while (query.next()) {
        QVariantList item;
        for (std::size_t i = 0; i < colsCount; ++i)
            item.push_back(query.value(i));
        result.push_back(item);
    }

    query.finish();
    return result;
}

bool DatabaseModel::insertRow(const QString& statement, const QVariantMap& values) const {
    QSqlQuery query(impl->database);

    if (!query.prepare(statement)) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }

    QStringList fieldNames = values.keys();
    std::for_each(fieldNames.begin(), fieldNames.end(), [&values, &query](const QString& name) {
            query.bindValue(name, values.value(name), QSql::In);
    });

    if (!query.exec()) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }
    query.finish();
    return true;
}

bool DatabaseModel::insertRow(const QString& statement) {
    QSqlQuery query(impl->database);

    if (!query.prepare(statement) || !query.exec()) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }
    query.finish();
    return true;
}
bool DatabaseModel::updateRow(const QString& statement, const QVariantMap& values) const {
    QSqlQuery query(impl->database);

    if (!query.prepare(statement)) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }

    QStringList fieldNames = values.keys();
    std::for_each(fieldNames.begin(), fieldNames.end(), [&values, &query](const QString& name) {
            query.bindValue(name, values.value(name), QSql::In);
    });

    if (!query.exec()) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }
    query.finish();
    return true;
}

bool DatabaseModel::updateRow(const QString& statement) {
    QSqlQuery query(impl->database);

    if (!query.prepare(statement) || !query.exec()) {
        qDebug() << "incorrect statement: " << statement;
        return false;
    }
    query.finish();
    return true;
}

void DatabaseModel::deleteRow(const QString& statement) const {
    QSqlQuery query(impl->database);

    if (!query.prepare(statement) || !query.exec()) {
        qDebug() << "incorrect statemtn: " << statement;
        return;
    }
    query.finish();
}

FT::data::DatabaseModel::DatabaseModel() {
    impl = new Implementation();
}

FT::data::DatabaseModel::~DatabaseModel() { }



} //data
}//ft
