
#include "ExerciseTypePieChart.hpp"

#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE

namespace FT {
namespace ui {

class ExerciseTypePieChart::Implementation
{
public:
    Implementation(ExerciseTypePieChart* obj): parent(obj) {

        series->setLabelsPosition(QPieSlice::LabelInsideNormal);

        chart->addSeries(series);
        chart->setTitle("Exercise Types Taken");
        chartView->setRenderHint(QPainter::Antialiasing);

    }

    QPieSeries* series{new QPieSeries()};
    QChart* chart{new QChart()};
    QChartView* chartView{new QChartView(chart)};


    ExerciseTypePieChart* parent;
};

ExerciseTypePieChart::ExerciseTypePieChart(controllers::StatisticsController* cont,
                                           QWidget *parent) : QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));
}

ExerciseTypePieChart::~ExerciseTypePieChart() { }

} //ui
} //FT
