#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace FT {
namespace controllers {

class StatisticsController;

} //controllers
} //FT

namespace FT {
namespace ui {

class StatisticsWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(StatisticsWindow)
public:
    explicit StatisticsWindow(controllers::StatisticsController*, QWidget *parent = nullptr);
    virtual ~StatisticsWindow() override;

private:

    class Implementation;
    QScopedPointer<Implementation> impl;
    controllers::StatisticsController* controller;
};

} //ui
} //FT

