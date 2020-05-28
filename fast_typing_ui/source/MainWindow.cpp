
#include "MainWindow.hpp"
#include "WindowFactory.hpp"

#include <QTabWidget>
#include <QDebug>

namespace FT {
namespace ui {


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    slotLoginWindow();
}

void MainWindow::slotRegisterWindow() {
    QMainWindow* regWindow = (QMainWindow*)framework::WindowFactory::createRegistrationWindow();
    setCentralWidget(regWindow);
    setFixedSize(regWindow->size());
    setWindowTitle(regWindow->windowTitle());
    connect(regWindow, SIGNAL(loginState()), SLOT(slotLoginWindow()));
}

void MainWindow::slotLoginWindow() {
    QMainWindow* logWindow = (QMainWindow*)framework::WindowFactory::createLoginWindow();
    setCentralWidget(logWindow);
    setFixedSize(logWindow->size());
    setWindowTitle(logWindow->windowTitle());
    connect(logWindow, SIGNAL(registerState()), SLOT(slotRegisterWindow()));
    connect(logWindow, SIGNAL(mainState()), SLOT(slotMainWindow()));
}

void MainWindow::slotMainWindow() {

    QTabWidget* mainw = new QTabWidget();
    mainw->setMovable(true);
    mainw->addTab((QMainWindow*)framework::WindowFactory::createAccountWindow(), tr("Account"));
    mainw->addTab((QMainWindow*)framework::WindowFactory::createExerciseWindow(), tr("Exercise"));
    mainw->addTab((QMainWindow*)framework::WindowFactory::createStatisticsWindow(), tr("Statistics"));
    mainw->addTab((QMainWindow*)framework::WindowFactory::createSettingsWindow(), tr("Settings"));

    takeCentralWidget();
    setCentralWidget(mainw);
    setSizePolicy(mainw->sizePolicy());
    setMinimumSize(0, 0);
    setMaximumSize(mainw->maximumSize());
    resize(mainw->size());
    setWindowTitle("Tabs");
}


} //ui
} //FT
