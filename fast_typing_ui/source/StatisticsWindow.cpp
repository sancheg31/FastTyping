

#include "StatisticsWindow.hpp"

#include "controllers/StatisticsController.hpp"
#include "ExerciseTypePieChart.hpp"
#include "ExercisePointsBarChart.hpp"

#include <QLabel>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace FT {
namespace ui {

class StatisticsWindow::Implementation
{
public:
    Implementation(StatisticsWindow* obj): parent(obj) {

        titleLabel->setFont(QFont("Calibri", 30, 50));
        titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        titleLabel->setWordWrap(true);
        titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        registerDateValue->setText(parent->controller->registerDate());
        charactersValue->setText(QString("%1").arg(parent->controller->characters()));
        significanceValue->setText(QString("%1").arg(parent->controller->significance()));
        errorsValue->setText(QString("%1").arg(parent->controller->errors()));
        //rewrite labels to be appropriate form

        QObject::connect(chart1, SIGNAL(clicked()), parent, SLOT(slotFirstChartClicked()));
        QObject::connect(chart2, SIGNAL(clicked()), parent, SLOT(slotSecondChartClicked()));
    }

    StatisticsWindow* parent;

    QLabel* titleLabel{new QLabel("Statistics")};

    QLabel* registerDateText{new QLabel("Register Date:")};
    QLabel* registerDateValue{new QLabel()};

    QLabel* charactersText{new QLabel("Characters: ")};
    QLabel* charactersValue{new QLabel()};

    QLabel* significanceText{new QLabel("Significance: ")};
    QLabel* significanceValue{new QLabel()};

    QLabel* errorsText{new QLabel("Errors: ")};
    QLabel* errorsValue{new QLabel()};

    QPushButton* chart1{new QPushButton("chart1")};
    QPushButton* chart2{new QPushButton("chart2")};


};

void StatisticsWindow::slotFirstChartClicked() {
    ExerciseTypePieChart* chart = new ExerciseTypePieChart(controller);
    chart->setAttribute(Qt::WA_DeleteOnClose);
    chart->setWindowTitle("Exercise Types Taken");
    chart->show();
}

void StatisticsWindow::slotSecondChartClicked() {
    ExercisePointsBarChart* chart = new ExercisePointsBarChart(controller);
    chart->setAttribute(Qt::WA_DeleteOnClose);
    chart->setWindowTitle("Recent Exercises");
    chart->show();
}


StatisticsWindow::StatisticsWindow(controllers::StatisticsController* cont,
                                   QWidget* parent): QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));

    QVBoxLayout* mainl = new QVBoxLayout();
    mainl->setSpacing(4);
    mainl->setContentsMargins(15, 15, 15, 20);

    mainl->addWidget(impl->titleLabel, Qt::AlignLeft);

    QHBoxLayout* datel = new QHBoxLayout();
    datel->addWidget(impl->registerDateText);
    datel->addWidget(impl->registerDateValue);
    datel->setSizeConstraint(QLayout::SetFixedSize);
    datel->setSpacing(8);
    datel->setContentsMargins(0, 0, 0, 0);

    QWidget* datew = new QWidget();
    datew->setLayout(datel);
    mainl->addWidget(datew);

    QHBoxLayout* timel = new QHBoxLayout();
    timel->addWidget(impl->charactersText);
    timel->addWidget(impl->charactersValue);
    timel->setSpacing(8);
    timel->setContentsMargins(0, 0, 0, 0);
    timel->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* timew = new QWidget();
    timew->setLayout(timel);
    mainl->addWidget(timew);

    QHBoxLayout* lessonsl = new QHBoxLayout();
    lessonsl->addWidget(impl->significanceText);
    lessonsl->addWidget(impl->significanceValue);
    lessonsl->setSpacing(8);
    lessonsl->setContentsMargins(0, 0, 0, 0);
    lessonsl->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* lessonsw = new QWidget();
    lessonsw->setLayout(lessonsl);
    mainl->addWidget(lessonsw);

    QHBoxLayout* errorl = new QHBoxLayout();
    errorl->addWidget(impl->errorsText);
    errorl->addWidget(impl->errorsValue);
    errorl->setSpacing(8);
    errorl->setContentsMargins(0, 0, 0, 0);
    errorl->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* errorw = new QWidget();
    errorw->setLayout(errorl);
    mainl->addWidget(errorw);

    QHBoxLayout* buttonl = new QHBoxLayout();
    buttonl->addWidget(impl->chart1);
    buttonl->addWidget(impl->chart2);
    buttonl->setSpacing(4);
    buttonl->setContentsMargins(0, 0, 0, 0);
    buttonl->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* buttonw = new QWidget();
    buttonw->setLayout(buttonl);
    mainl->addWidget(buttonw);
    mainl->setAlignment(buttonw, Qt::AlignCenter);

    QWidget* w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);

}

StatisticsWindow::~StatisticsWindow() { }






} //ui
} //FT


