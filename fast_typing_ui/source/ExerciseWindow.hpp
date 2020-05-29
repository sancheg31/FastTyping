#pragma once

#include <QTreeWidget>


namespace FT::controllers {

class ExerciseController;

}

namespace FT {
namespace ui {

class ExerciseWindow: public QTreeWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExerciseWindow)
public:
    ExerciseWindow(controllers::ExerciseController*, QWidget* parent = nullptr);
    virtual ~ExerciseWindow() override;


private:
    controllers::ExerciseController* controller;

};

} //ui
} //FT

