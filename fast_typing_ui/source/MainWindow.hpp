#pragma once

#include <QMainWindow>

namespace FT::controllers {

class RegistrationController;
class AccountController;
class ExerciseController;
class SettingsController;
class StatisticsController;

}

namespace FT {
namespace ui {

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void slotRegisterWindow();
    void slotLoginWindow();
    void slotLoginWindow(const QString& login, const QString& password);
    void slotMainWindow();

    void slotApplicationStyleChanged(const QString& newStyle);


private:
    controllers::RegistrationController* regController;
    controllers::AccountController* accountController;
    controllers::SettingsController* settingsController;
    controllers::StatisticsController* statController;
    controllers::ExerciseController* exController;
};

} //ui
} //FT

