
#include "SettingsController.hpp"

#include <QDebug>

#include <algorithm>

#include "DatabaseModel.hpp"
#include "AccountController.hpp"

namespace FT {
namespace controllers {

class SettingsController::Implementation
{
public:
    Implementation(SettingsController* obj): parent(obj) {
        styles = loadStyles();
        curStyleIndex = styles.indexOf(loadAccountStyle());
        qDebug() << styles;
        qDebug() << curStyleIndex << ' ' << styles[curStyleIndex];
        layouts = loadLayouts();
        curLayoutIndex = layouts.indexOf(loadAccountLayout());
        qDebug() << layouts;
        qDebug() << curLayoutIndex << ' ' << layouts[curLayoutIndex];
    }

    SettingsController* parent;

    QStringList styles;
    QStringList layouts;

    std::size_t curStyleIndex;
    std::size_t curLayoutIndex;

    //returns all operating system names from the table
    QStringList loadStyles() {
        const static QString query = "SELECT type FROM OperatingSystem";
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        QStringList result;
        std::transform(list.begin(), list.end(), std::back_inserter(result), [](QVariantList& s) {
             return qvariant_cast<QString>(s[0]);
        });
        return result;
    }

    //returns all layouts from the table
    QStringList loadLayouts() {
        const static QString query = "SELECT name FROM KeyboardLayout";
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        QStringList result;
        std::transform(list.begin(), list.end(), std::back_inserter(result), [](QVariantList& s) {
             return qvariant_cast<QString>(s[0]);
        });
        return result;
    }

    //returns account's layout saved in AccountSettings
    QString loadAccountLayout() {
        QString query = QString("SELECT name FROM "
                                "KeyboardLayout INNER JOIN AccountSettings "
                                "ON KeyboardLayout.id = AccountSettings.keyboard_layout_id "
                                "WHERE AccountSettings.user_id = %1").arg(parent->accountController->accountId());
        qDebug() << parent->accountController->accountId();
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        qDebug() << list;
        return qvariant_cast<QString>(list[0][0]);
    }

    //returns account's operating system name saved in AccountSettings
    QString loadAccountStyle() {
        QString query = QString("SELECT type FROM "
                                "OperatingSystem INNER JOIN AccountSettings "
                                "ON OperatingSystem.id = AccountSettings.operating_system_id "
                                "WHERE AccountSettings.user_id = %1").arg(parent->accountController->accountId());

        auto list = data::DatabaseModel::instance().selectRows(query).value();
        qDebug() << list;
        return qvariant_cast<QString>(list[0][0]);
    }

};

void SettingsController::setCurrentStyle(const QString& style) {
    int index = impl->styles.indexOf(style);

    if (index == -1 || (std::size_t)index == impl->curStyleIndex)
        return;

    QString query = QString("UPDATE AccountSettings "
                            "SET operating_system_id = ("
                            "SELECT id FROM OperatingSystem WHERE type = \"%1\""
                            ") WHERE user_id = %2").arg(style).arg(accountController->accountId());

    bool updated = data::DatabaseModel::instance().updateRow(query);

    if (!updated) {
        qDebug() << "unable to update with style: " << style
                 << " for id: " << accountController->accountId();
    }

    std::size_t temp = impl->curStyleIndex;
    impl->curStyleIndex = index;
    qDebug() << "current style changed: " << impl->styles[index];
    emit currentStyleChanged(impl->styles[index], impl->styles[temp]);

}

void SettingsController::setCurrentLayout(const QString& layout) {
    int index = impl->layouts.indexOf(layout);

    if (index == -1 || (std::size_t) index == impl->curLayoutIndex)
        return;

    QString query = QString("UPDATE AccountSettings "
                            "SET keyboard_layout_id = ("
                            "SELECT id FROM KeyboardLayout WHERE name = \"%1\""
                            ") WHERE user_id = %2").arg(layout).arg(accountController->accountId());

    bool updated = data::DatabaseModel::instance().updateRow(query);

    if (!updated) {
        qDebug() << "unable to update layout: " << layout
                 << "for id: " << accountController->accountId();
    }

    std::size_t temp = impl->curLayoutIndex;
    impl->curLayoutIndex = index;
    qDebug() << "current layout changed: " << impl->layouts[index];
    emit currentLayoutChanged(impl->layouts[index], impl->layouts[temp]);
}

QString SettingsController::currentStyle() const {
    return impl->styles[impl->curStyleIndex];
}

int SettingsController::currentStyleIndex() const {
    return impl->curStyleIndex;
}

QString SettingsController::currentLayout() const {
    return impl->layouts[impl->curLayoutIndex];
}

int SettingsController::currentLayoutIndex() const {
    return impl->curLayoutIndex;
}


QStringList SettingsController::styles() const {
    return impl->styles;
}

QStringList SettingsController::layouts() const {
    return impl->layouts;
}

SettingsController::SettingsController(AccountController* cont,
                                       QObject* parent): QObject(parent), accountController(cont)  {
    impl.reset(new Implementation(this));
}

/*virtual*/ SettingsController::~SettingsController() { }


} //controllers
} //FT
