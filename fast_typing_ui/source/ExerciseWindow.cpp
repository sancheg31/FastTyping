
#include "ExerciseWindow.hpp"

#include "controllers/ExerciseController.hpp"

namespace FT {
namespace ui {

ExerciseWindow::ExerciseWindow(controllers::ExerciseController* cont,
                               QWidget* parent): QTreeWidget(parent), controller(cont) {

    setHeaderItem(new QTreeWidgetItem(QStringList() << "Exercises"));
    QStringList types = controller->exerciseTypes();

    QList<QTreeWidgetItem*> items;
    for (auto & type: types) {
        auto item = new QTreeWidgetItem(QStringList() << type);
        QStringList names = controller->exerciseNames(type);
        for (auto & name: names) {
            item->addChild(new QTreeWidgetItem(QStringList() << name));
        }
        items.append(item);
    }
    insertTopLevelItems(0, items);
}


ExerciseWindow::~ExerciseWindow() { }



} //ui
} //FT
