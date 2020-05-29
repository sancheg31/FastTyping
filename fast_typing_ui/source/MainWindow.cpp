
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
#include <QMenuBar>

#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QVariant>

#include "DatabaseModel.hpp"

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

    QMenu* excel = menuBar()->addMenu("excel");
    excel->addAction("print to excel", this, SLOT(slotPrintToExcel()));

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



void MainWindow::slotPrintToExcel() {

    QString statement = "SELECT login, email, password FROM Account";
    auto result = FT::data::DatabaseModel::instance().selectRows(statement).value();

    qDebug() << result;

    QAxObject *mExcel = new QAxObject( "Excel.Application", this);
    QAxObject *workbooks = mExcel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", "D:\\1.xlsx");
    QAxObject *mSheets = workbook->querySubObject("Sheets");
    QAxObject *StatSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant("Sheet1") );

    for (int row = 1; row <= result.size(); ++row)
        for (int col = 1; col <= result[row-1].size(); ++col) {
            QAxObject* cell = StatSheet->querySubObject("Cells(QVariant,QVariant)", row, col);
            cell->setProperty("Value", QVariant(result[row - 1][col - 1]));
            delete cell;
        }

    workbook->dynamicCall("Save()" );
    workbook->dynamicCall("Close()");
    mExcel->dynamicCall("Quit ()");

    delete StatSheet;
    delete mSheets;
    delete workbook;
    delete workbooks;
    delete mExcel;

}



} //ui
} //FT
