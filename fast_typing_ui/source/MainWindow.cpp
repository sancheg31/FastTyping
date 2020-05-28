
#include "MainWindow.hpp"
#include "WindowFactory.hpp"

#include <QDebug>

namespace FT {
namespace ui {


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    slotLoginWindow();
}

void MainWindow::slotRegisterWindow() {
    ui::RegistrationWindow* regWindow = framework::WindowFactory::createRegistrationWindow();
    setCentralWidget(regWindow);
    setFixedSize(regWindow->size());
    setWindowTitle(regWindow->windowTitle());
    connect(regWindow, SIGNAL(loginState()), SLOT(slotLoginWindow()));
}

void MainWindow::slotLoginWindow() {
    ui::LoginWindow* logWindow = framework::WindowFactory::createLoginWindow();
    setCentralWidget(logWindow);
    setFixedSize(logWindow->size());
    setWindowTitle(logWindow->windowTitle());
    connect(logWindow, SIGNAL(registerState()), SLOT(slotRegisterWindow()));
    connect(logWindow, SIGNAL(mainState()), SLOT(slotMainWindow()));
}

void MainWindow::slotMainWindow() {
    QTabWidget* mainw = new QTabWidget();
    mainw->setWindowTitle("tabs");
    mainw->addTab((QMainWindow*)framework::WindowFactory::createAccountWindow(), "Account");
    mainw->addTab(new QWidget(), "Lessons");
    mainw->addTab((QMainWindow*)framework::WindowFactory::createStatisticsWindow(), "Statistics");
    mainw->addTab((QMainWindow*)framework::WindowFactory::createSettingsWindow(), "Settings");
    qDebug() << "success: " << takeCentralWidget();
    setCentralWidget(mainw);
    setSizePolicy(mainw->sizePolicy());
    setMinimumSize(mainw->minimumSize());
    setMaximumSize(mainw->maximumSize());
    resize(mainw->size());
    setWindowTitle(mainw->windowTitle());
}


} //ui
} //FT
