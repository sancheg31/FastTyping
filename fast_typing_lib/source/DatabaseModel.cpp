
#include "DatabaseModel.hpp"

#include <QString>
#include <QVariant>
#include <QtSql>

#include <QDebug>

#include <exception>

namespace FT {
namespace data {


class DatabaseModel::Implementation
{
public:
    Implementation(DatabaseModel* model): dbModel(model) {
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

    DatabaseModel* dbModel;
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

/*static*/ QScopedPointer<DatabaseModel::Implementation> DatabaseModel::impl{};
/*static*/ DatabaseModel* DatabaseModel::pinstance{nullptr};
/*static*/ bool DatabaseModel::destroyed{false};

/*static*/ FT::data::DatabaseModel& FT::data::DatabaseModel::instance() {
    if (!pinstance) {
        if (!destroyed) {
            create();
        } else {
            onDeadReference();
        }
    }
    return *pinstance;
}

std::optional<QList<QVariantList>> DatabaseModel::selectRows(const QString& statement) const {
    QSqlQuery query(impl->database);
    query.setForwardOnly(true);

    if (!query.prepare(statement) || !query.exec()) {
        return {};
    }

    std::size_t colsCount = query.record().count();
    QList<QVariantList> result;

    while (query.next()) {
        QVariantList item;
        for (std::size_t i = 0; i < colsCount; ++i)
            item.push_back(query.value(i));
        result.push_back(item);
    }

    query.finish();
    return std::optional{result};
}

FT::data::DatabaseModel::DatabaseModel() {
    impl.reset(new Implementation(this));
}

FT::data::DatabaseModel::~DatabaseModel() {
    delete pinstance;
    destroyed = true;
}


/*static*/ void FT::data::DatabaseModel::create() {
    static DatabaseModel instance_;
    pinstance = &instance_;
}

/*static*/ void FT::data::DatabaseModel::onDeadReference() {
    throw std::runtime_error("Dangling reference in DatabaseModel");
}


} //data
}//ft
