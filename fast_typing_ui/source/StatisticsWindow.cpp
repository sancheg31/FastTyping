

#include "StatisticsWindow.hpp"

#include <QLabel>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace FT {
namespace ui {


class ExerciseTypePieChart;
class ExercisePointBarChart;

class StatisticsWindow::Implementation
{
public:
    Implementation(StatisticsWindow* obj): parent(obj) {

        titleLabel->setFont(QFont("Calibri", 30, 100));
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(true);


        //rewrite labels to be appropriate form
    }

    StatisticsWindow* parent;

    QLabel* titleLabel{new QLabel("Statistics")};

    QLabel* registerDateText{new QLabel("Register Date:")};
    QLabel* registerDateValue{new QLabel("0")};

    QLabel* timeSpentText{new QLabel("Time spent: ")};
    QLabel* timeSpentValue{new QLabel("10")};

    QLabel* lessonsTakenText{new QLabel("Exercise taken:")};
    QLabel* lessonsTakenValue{new QLabel("100")};

    QLabel* errorRateText{new QLabel("Error rate:")};
    QLabel* errorRateValue{new QLabel("1000")};

    QPushButton* chart1{new QPushButton("chart1")};
    QPushButton* chart2{new QPushButton("chart2")};

    ExerciseTypePieChart* pieChart;
    ExercisePointBarChart* barChart;


};

StatisticsWindow::StatisticsWindow(controllers::StatisticsController* cont,
                                   QWidget* parent): QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));

    QVBoxLayout* mainl = new QVBoxLayout();
    //mainl->setSizeConstraint(QLayout::SetFixedSize);
    mainl->setSpacing(4);
    mainl->setContentsMargins(15, 15, 15, 30);

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
    timel->addWidget(impl->timeSpentText);
    timel->addWidget(impl->timeSpentValue);
    timel->setSpacing(8);
    timel->setContentsMargins(0, 0, 0, 0);
    timel->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* timew = new QWidget();
    timew->setLayout(timel);
    mainl->addWidget(timew);

    QHBoxLayout* lessonsl = new QHBoxLayout();
    lessonsl->addWidget(impl->lessonsTakenText);
    lessonsl->addWidget(impl->lessonsTakenValue);
    lessonsl->setSpacing(8);
    lessonsl->setContentsMargins(0, 0, 0, 0);
    lessonsl->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* lessonsw = new QWidget();
    lessonsw->setLayout(lessonsl);
    mainl->addWidget(lessonsw);

    QHBoxLayout* errorl = new QHBoxLayout();
    errorl->addWidget(impl->errorRateText);
    errorl->addWidget(impl->errorRateValue);
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


