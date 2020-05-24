#pragma once


#include <QScopedPointer>
#include <QList>
#include <QMap>
#include <QVariant>

#include <optional>

#include "ft_lib_global.h"

class QSqlQuery;

namespace FT {
namespace data {

    class CMLIB_EXPORT DatabaseModel
    {
    public:

        static DatabaseModel& instance();

        std::optional<QList<QVariantList>> selectRows(const QString& statement) const;
        std::optional<QVariantMap> insertRows(const QString& statement, const QVariantMap& values) const;
        std::optional<QVariantMap> updateRows(const QString& statement, const QVariantMap& values) const;
        std::optional<QVariantMap> deleteRows(const QString& statement) const;

    private:

        DatabaseModel();
        virtual ~DatabaseModel();

        DatabaseModel(const DatabaseModel&) = delete;
        DatabaseModel(DatabaseModel&&) = delete;
        DatabaseModel& operator=(const DatabaseModel&) = delete;
        DatabaseModel& operator=(DatabaseModel&&) = delete;

        class Implementation;
        static QScopedPointer<Implementation> impl;
        static DatabaseModel* pinstance;
        static bool destroyed;



        static void create();
        static void onDeadReference();

    };



} //data
} //ft

