#pragma once

#include <QObject>

namespace FT {
namespace controllers {

class AccountController;

class StatisticsController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(StatisticsController)
public:
    explicit StatisticsController(AccountController*, QObject *parent = nullptr);
    virtual ~StatisticsController() override;


    QMap<QString, int> exerciseNamesAndCounts() const;

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    AccountController* accountController;

};


} //controllers
} //FT

