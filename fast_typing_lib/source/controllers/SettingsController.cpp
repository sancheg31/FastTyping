
#include "SettingsController.hpp"

#include <QDebug>

#include <algorithm>

#include "DatabaseModel.hpp"

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
        const static QString query = "SELECT name FROM "
                                     "KeyboardLayout INNER JOIN AccountSettings "
                                     "ON KeyboardLayout.id = AccountSettings.keyboard_layout_id";
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        qDebug() << list;
        return qvariant_cast<QString>(list[0][0]);
    }

    //returns account's operating system name saved in AccountSettings
    QString loadAccountStyle() {
        const static QString query = "SELECT type FROM "
                                     "OperatingSystem INNER JOIN AccountSettings "
                                     "ON OperatingSystem.id = AccountSettings.operating_system_id";
        auto list = data::DatabaseModel::instance().selectRows(query).value();
        qDebug() << list;
        return qvariant_cast<QString>(list[0][0]);
    }

};

QString SettingsController::currentStyle() const {
    return impl->styles[impl->curStyleIndex];
}

QString SettingsController::currentLayout() const {
    return impl->layouts[impl->curLayoutIndex];
}

void SettingsController::setCurrentStyle(const QString& style) {
    int index = impl->styles.indexOf(style);
    if (index != -1 && (std::size_t)index != impl->curStyleIndex) {
        std::size_t temp = impl->curStyleIndex;
        impl->curStyleIndex = index;
        qDebug() << "current style changed: " << impl->styles[index];
        emit currentStyleChanged(impl->styles[index], impl->styles[temp]);
    }
}

void SettingsController::setCurrentLayout(const QString& layout) {
    int index = impl->layouts.indexOf(layout);
    if (index != -1 && (std::size_t)index != impl->curLayoutIndex) {
        std::size_t temp = impl->curLayoutIndex;
        impl->curLayoutIndex = index;
        qDebug() << "current layout changed: " << impl->layouts[index];
        emit currentLayoutChanged(impl->layouts[index], impl->layouts[temp]);
    }
}

QStringList SettingsController::styles() const {
    return impl->styles;
}

QStringList SettingsController::layouts() const {
    return impl->layouts;
}

SettingsController::SettingsController() {
    impl.reset(new Implementation(this));
}

/*virtual*/ SettingsController::~SettingsController() { }


} //controllers
} //FT
