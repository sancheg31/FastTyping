#pragma once

#include <QObject>

namespace FT {
namespace controllers {

class AccountController;

class StatisticsController : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(StatisticsController)

    Q_PROPERTY(int ui_characters READ characters)
    Q_PROPERTY(int ui_significance READ significance)
    Q_PROPERTY(int ui_errors READ errors)
    Q_PROPERTY(QString ui_registerDate READ registerDate)

public:
    explicit StatisticsController(AccountController*, QObject *parent = nullptr);
    virtual ~StatisticsController() override;


    int characters() const;
    int errors() const;
    int significance() const;
    QString registerDate() const;

    QMap<QString, int> exerciseNamesAndCounts() const;

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    AccountController* accountController;

};


} //controllers
} //FT

