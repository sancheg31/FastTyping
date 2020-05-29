
#include "ExercisePointsBarChart.hpp"

#include "controllers/StatisticsController.hpp"

#include <algorithm>

#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>

#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

namespace FT {
namespace ui {

class ExercisePointsBarChart::Implementation
{
public:
    Implementation(ExercisePointsBarChart* obj): parent(obj) {
        values = parent->controller->exercisesTaken();

        QStringList titles;
        titles << "chars" << "duration" << "errors" << "points";

        int position = 0;
        qDebug() << values.size();
        std::for_each(titles.begin(), titles.end(), [this, &position](const QString& title) {
            QBarSet* set = new QBarSet(title);
            for (int i = 0; i < values.size(); ++i) {
                *set << values[i][position].toInt();
            }
            series->append(set);
            ++position;
        });

        chart->addSeries(series);
        chart->setTitle("Recent Exercises");
        chart->setTitleFont(QFont("Arial", 20, 10));
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        for (int i = 0; i < values.size(); ++i) {
            categories << values[i][position].toString() + QString(i, '\0');
        }
        qDebug() << "categories size: " << categories.size();

        QBarCategoryAxis* x = new QBarCategoryAxis();
        x->setCategories(categories);
        chart->addAxis(x, Qt::AlignBottom);
        series->attachAxis(x);

        QValueAxis* y = new QValueAxis();
        y->setRange(0, 1000);
        y->setTickInterval(100);
        chart->addAxis(y, Qt::AlignLeft);
        series->attachAxis(y);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    }

    ExercisePointsBarChart* parent;

    QList<QVariantList> values;
    QBarSeries* series{new QBarSeries()};
    QChart* chart{new QChart()};
    QChartView* chartView{nullptr};
};

ExercisePointsBarChart::ExercisePointsBarChart(controllers::StatisticsController* cont,
                                               QWidget *parent) : QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));
    setCentralWidget(impl->chartView);
    resize(impl->chartView->size());
}

ExercisePointsBarChart::~ExercisePointsBarChart() { }



} //ui
} //FT

