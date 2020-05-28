#pragma once

#include <QMainWindow>
#include <QScopedPointer>


namespace FT::controllers {

class StatisticsController;

}

namespace FT {
namespace ui {

class ExerciseTypePieChart : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExerciseTypePieChart)
public:
    explicit ExerciseTypePieChart(controllers::StatisticsController*, QWidget *parent = nullptr);
    virtual ~ExerciseTypePieChart() override;

    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::StatisticsController* controller;

};

} //ui
} //FT



