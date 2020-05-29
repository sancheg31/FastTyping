
#include "ExerciseTypePieChart.hpp"

#include "controllers/StatisticsController.hpp"

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

        series->setLabelsPosition(QPieSlice::LabelOutside);

        auto pieValues = parent->controller->exerciseNamesAndCounts();
        QStringList names = pieValues.keys();

        for (auto it = names.begin(); it != names.end(); ++it) {
            QPieSlice* slice = series->append(*it, pieValues.value(*it));
            if (slice->value() > 0) {
                slice->setLabelVisible(true);
            }
        }

        chart->addSeries(series);
        chart->legend()->setVisible(false);
        chart->setTitle("Exercise Types Taken");
        chart->setTitleFont(QFont("Arial", 20, 10));
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
    setCentralWidget(impl->chartView);
    setMinimumSize(impl->chartView->size());
    resize(impl->chartView->size());
}

ExerciseTypePieChart::~ExerciseTypePieChart() { }

} //ui
} //FT
