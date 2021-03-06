#pragma once


#include <QObject>

#include <QScopedPointer>
#include <QString>
#include <QStringList>

#include "ft_lib_global.h"

namespace FT {
namespace controllers {

class AccountController;

class FT_LIB_EXPORT SettingsController: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(SettingsController)
    Q_PROPERTY(QString ui_current_style READ currentStyle WRITE setCurrentStyle NOTIFY currentStyleChanged)
    Q_PROPERTY(QString ui_current_layout READ currentLayout WRITE setCurrentStyle NOTIFY currentLayoutChanged)
public:
    explicit SettingsController(AccountController*, QObject* parent = nullptr);
    virtual ~SettingsController() override;

    QString currentStyle() const;
    int currentStyleIndex() const;
    QString currentLayout() const;
    int currentLayoutIndex() const;

    void setCurrentStyle(const QString& style);
    void setCurrentLayout(const QString& layout);

    QStringList styles() const;
    QStringList layouts() const;

signals:
    void currentStyleChanged(const QString& news, const QString& olds);
    void currentLayoutChanged(const QString& news, const QString& olds);

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    AccountController* accountController;
};

} //controllers
} //FT



