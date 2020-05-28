
#include "StatisticsController.hpp"

#include "DatabaseModel.hpp"
#include "AccountController.hpp"

#include <QStringList>
#include <QVector>
#include <QMap>

#include <algorithm>

namespace FT {
namespace controllers {

class StatisticsController::Implementation
{
public:
    Implementation(StatisticsController* obj): parent(obj) {
        exerciseTypes = loadExerciseTypes();
        exerciseTakenPerType = loadExerciseTakenPerType(exerciseTypes.keys(),
                                                        parent->accountController->accountId());

        QString selectAccountData = QString("SELECT characters, significance, errors FROM AccountStatistics "
                                            "WHERE user_id = %1").arg(parent->accountController->accountId());

        auto list = data::DatabaseModel::instance().selectRows(selectAccountData).value();

        characters = list[0][0].toInt();
        significance = list[0][1].toInt();
        errors = list[0][2].toInt();

        QString selectRegisterDate = QString("SELECT created_at FROM Account WHERE user_id = %1")
                                     .arg(parent->accountController->accountId());

        auto list2 = data::DatabaseModel::instance().selectRows(selectRegisterDate).value();
        registerDate = list2[0][0].toString();

    }
    StatisticsController* parent;

    QMap<int, QString> exerciseTypes;
    QMap<int, int> exerciseTakenPerType;

    int characters;
    int significance;
    int errors;
    QString registerDate;

    QMap<int, QString> loadExerciseTypes() {

        QString statement = QString("SELECT id, name FROM ExerciseType");
        auto list = data::DatabaseModel::instance().selectRows(statement).value();

        QMap<int, QString> result;
        std::for_each(list.begin(), list.end(), [&result](auto& l) {
            result.insert(l[0].toInt(), l[1].toString());
        });
        return result;
    }

    QMap<int, int> loadExerciseTakenPerType(const QList<int>& keys, int id) {

        QMap<int, int> result;
        std::for_each(keys.begin(), keys.end(), [&id, &result](int ex_id) {
            QString statement = QString("SELECT COUNT(exercise_id) FROM AccountExerciseHistory "
                                "WHERE user_id = %1 AND exercise_id = %2").arg(id).arg(ex_id);
            auto value = data::DatabaseModel::instance().selectRows(statement).value()[0][0].toInt();
            result.insert(ex_id, value);
        });
        return result;
    }


};

QMap<QString, int> StatisticsController::exerciseNamesAndCounts() const {
    QList<int> keys = impl->exerciseTypes.keys();
    QMap<QString, int> result;

    std::for_each(keys.begin(), keys.end(), [&result, this](int id) {
        result.insert(impl->exerciseTypes.value(id), impl->exerciseTakenPerType.value(id));
    });

    return result;
}

StatisticsController::StatisticsController(AccountController* cont,
                                           QObject *parent) : QObject(parent), accountController(cont) {
    impl.reset(new Implementation(this));
}


/*virtual*/ StatisticsController::~StatisticsController() { }

int StatisticsController::characters() const {
    return impl->characters;
}

int StatisticsController::errors() const {
    return impl->errors;
}

int StatisticsController::significance() const {
    return impl->significance;
}

QString StatisticsController::registerDate() const {
    return impl->registerDate;
}


} //controllers
} //FT

