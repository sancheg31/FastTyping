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

class FT_LIB_EXPORT DatabaseModel
{
    Q_DISABLE_COPY_MOVE(DatabaseModel)
public:

    static DatabaseModel& instance();

    std::optional<QList<QVariantList>> selectRows(const QString& statement) const;
    std::optional<QVariantMap> insertRows(const QString& statement, const QVariantMap& values) const;
    std::optional<QVariantMap> updateRows(const QString& statement, const QVariantMap& values) const;
    std::optional<QVariantMap> deleteRows(const QString& statement) const;

private:

    DatabaseModel();
    virtual ~DatabaseModel();

    class Implementation;
    static Implementation* impl;

};



} //data
} //FT

