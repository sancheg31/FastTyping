
#include "MainWindow.hpp"
#include "WindowFactory.hpp"

#include <QApplication>
#include "controllers/RegistrationController.hpp"
#include "controllers/AccountController.hpp"
#include "controllers/SettingsController.hpp"
#include "controllers/StatisticsController.hpp"
#include "controllers/ExerciseController.hpp"

#include <QStyleFactory>
#include <QTabWidget>
#include <QDebug>
#include <QStyle>

using namespace FT::controllers;
using namespace FT::framework;

namespace FT {
namespace ui {


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    regController = new RegistrationController();
    accountController = new AccountController();
    slotLoginWindow();
}

void MainWindow::slotRegisterWindow() {
    QMainWindow* regWindow = (QMainWindow*)
                             WindowFactory::createRegistrationWindow(regController);

    setCentralWidget(regWindow);
    setFixedSize(regWindow->size());
    setWindowTitle(regWindow->windowTitle());
    connect(regWindow, SIGNAL(loginState()), SLOT(slotLoginWindow()));
    connect(regWindow, SIGNAL(loginState(QString, QString)), SLOT(slotLoginWindow(QString, QString)));
}

void MainWindow::slotLoginWindow() {
    QMainWindow* logWindow = (QMainWindow*)
                             WindowFactory::createLoginWindow(accountController);

    setCentralWidget(logWindow);
    setFixedSize(logWindow->size());
    setWindowTitle(logWindow->windowTitle());
    connect(logWindow, SIGNAL(registerState()), SLOT(slotRegisterWindow()));
    connect(logWindow, SIGNAL(mainState()), SLOT(slotMainWindow()));
}

void MainWindow::slotLoginWindow(const QString& login, const QString& password) {
    qDebug() << "\nlogin: " << login << "\npassword: " << password;
    accountController->loadAccountData(login, password);
    slotLoginWindow();
}

void MainWindow::slotMainWindow() {

    settingsController = new SettingsController(accountController);
    connect(settingsController, SIGNAL(currentStyleChanged(QString, QString)),
            this, SLOT(slotApplicationStyleChanged(QString)));

    slotApplicationStyleChanged(settingsController->currentStyle());

    statController = new StatisticsController(accountController);
    exController = new ExerciseController(accountController);


    QTabWidget* mainw = new QTabWidget();
    mainw->setMovable(true);
    mainw->addTab((QMainWindow*)WindowFactory::createAccountWindow(accountController), tr("Account"));
    mainw->addTab((QMainWindow*)WindowFactory::createExerciseWindow(exController), tr("Exercise"));
    mainw->addTab((QMainWindow*)WindowFactory::createStatisticsWindow(statController), tr("Statistics"));
    mainw->addTab((QMainWindow*)WindowFactory::createSettingsWindow(settingsController), tr("Settings"));

    takeCentralWidget();
    setCentralWidget(mainw);
    setSizePolicy(mainw->sizePolicy());
    setMinimumSize(0, 0);
    setMaximumSize(mainw->maximumSize());
    resize(mainw->size());
    setWindowTitle("Tabs");
}

void MainWindow::slotApplicationStyleChanged(const QString& newStyle) {
    QStyleFactory* factory = new QStyleFactory();
    if (newStyle == "Linux") {
        qApp->setStyle(factory->create("Fusion"));
    } else if (newStyle == "macOS") {
        qApp->setStyle(factory->create("windowsvista"));
    } else if (newStyle == "Windows") {
        qApp->setStyle(factory->create("Windows"));
    }
}



} //ui
} //FT
