#pragma once

#include <QObject>

#include "ft_lib_global.h"

namespace FT {
namespace controllers {

class AccountController;

class FT_LIB_EXPORT ExerciseController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExerciseController)

public:
    explicit ExerciseController(AccountController*, QObject *parent = nullptr);
    virtual ~ExerciseController() override;

    QStringList exerciseTypes() const;
    QStringList exerciseNames(const QString& type) const;

private:
    class Implementation;
    QScopedPointer<Implementation> impl;
    AccountController* accountController;

};

} //controllers
} //FT

