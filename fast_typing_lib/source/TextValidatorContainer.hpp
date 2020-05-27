#pragma once

#include <QScopedPointer>
#include <QRegExp>

#include "ft_lib_global.h"

namespace FT {
namespace data {

class FT_LIB_EXPORT TextValidatorContainer
{
    Q_DISABLE_COPY_MOVE(TextValidatorContainer)
public:

    static QRegExp getValidator(const QString& key);
    static bool addValidator(const QString& key, const QString& value);

private:

    TextValidatorContainer();

    static TextValidatorContainer& instance();

    class Implementation;
    QScopedPointer<Implementation> impl;
};


} //data
} //ft

