#pragma once

#include <QMainWindow>

namespace FT::controllers {

class StatisticsController;

}

namespace FT {
namespace ui {

class ExercisePointsBarChart : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExercisePointsBarChart)

public:
    explicit ExercisePointsBarChart(controllers::StatisticsController*, QWidget *parent = nullptr);
    virtual ~ExercisePointsBarChart() override;


private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::StatisticsController* controller;
};

} //ui
} //TF

