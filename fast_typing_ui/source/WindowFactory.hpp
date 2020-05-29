#pragma once

namespace FT::ui {

class LoginWindow;
class RegistrationWindow;
class AccountWindow;
class ExerciseWindow;
class SettingsWindow;
class StatisticsWindow;

}

namespace FT::controllers {

class RegistrationController;
class AccountController;
class ExerciseController;
class SettingsController;
class StatisticsController;

}

namespace FT {
namespace framework {

class WindowFactory
{

public:
    WindowFactory();
    ~WindowFactory();

    static ui::LoginWindow* createLoginWindow(controllers::AccountController* cont);
    static ui::RegistrationWindow* createRegistrationWindow(controllers::RegistrationController*);
    static ui::AccountWindow* createAccountWindow(controllers::AccountController*);
    static ui::ExerciseWindow* createExerciseWindow(controllers::ExerciseController*);
    static ui::StatisticsWindow* createStatisticsWindow(controllers::StatisticsController*);
    static ui::SettingsWindow* createSettingsWindow(controllers::SettingsController*);

};

} //framework
} // TF

