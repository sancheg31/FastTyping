
#include "ExerciseController.hpp"

#include "AccountController.hpp"
#include "DatabaseModel.hpp"

#include <algorithm>

#include <QMap>
#include <QStringList>

namespace FT {
namespace controllers {


class ExerciseController::Implementation
{
public:
    Implementation(ExerciseController* obj): parent(obj) {
        exerciseTypes = loadExerciseTypes();
        exerciseNames = loadExerciseNames(exerciseTypes.keys());
    }

    ExerciseController* parent;

    QMap<int, QString> exerciseTypes;

    QMap<int, QStringList> exerciseNames;


    QMap<int, QString> loadExerciseTypes() {
        QString statement = QString("SELECT id, name FROM ExerciseType");

        auto list = data::DatabaseModel::instance().selectRows(statement).value();

        QMap<int, QString> result;
        std::for_each(list.begin(), list.end(), [&result](auto & l) {
            result.insert(l[0].toInt(), l[1].toString());
        });
        return result;
    }

    QMap<int, QStringList> loadExerciseNames(const QList<int>& keys) {
        QMap<int, QStringList> result;

        std::for_each(keys.begin(), keys.end(), [&result](int key) {
            QString statement = QString("SELECT text FROM Exercise WHERE exercise_type_id = %1").arg(key);
            auto list = data::DatabaseModel::instance().selectRows(statement).value();
            QStringList names;
            std::transform(list.begin(), list.end(), std::back_inserter(names), [](auto & l) {
                return l[0].toString();
            });
            result.insert(key, names);
        });

        return result;
    }

};

QStringList ExerciseController::exerciseTypes() const {
    return impl->exerciseTypes.values();
}

QStringList ExerciseController::exerciseNames(const QString& type) const {
    return impl->exerciseNames.value(impl->exerciseTypes.key(type));
}

ExerciseController::ExerciseController(AccountController* cont,
                                       QObject* parent): QObject(parent), accountController(cont) {
    impl.reset(new Implementation(this));
}

ExerciseController::~ExerciseController() { }












} //controllers
} //FT
