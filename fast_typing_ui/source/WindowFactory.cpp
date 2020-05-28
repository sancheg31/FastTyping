
#include "WindowFactory.hpp"


#include "AccountWindow.hpp"
#include "LoginWindow.hpp"
#include "StatisticsWindow.hpp"
#include "RegistrationWindow.hpp"
#include "SettingsWindow.hpp"

#include "controllers/SettingsController.hpp"
#include "controllers/AccountController.hpp"
#include "controllers/RegistrationController.hpp"

namespace FT {
namespace framework {


ui::LoginWindow* WindowFactory::createLoginWindow(controllers::AccountController* cont) {
    return new ui::LoginWindow(cont);
}

ui::RegistrationWindow* WindowFactory::createRegistrationWindow(controllers::RegistrationController* cont) {
    return new ui::RegistrationWindow(cont);
}

ui::AccountWindow* WindowFactory::createAccountWindow(controllers::AccountController* cont) {
    return new ui::AccountWindow(cont);
}

ui::ExerciseWindow* WindowFactory::createExerciseWindow() {
    return nullptr;
}

ui::StatisticsWindow* WindowFactory::createStatisticsWindow(controllers::StatisticsController* cont) {
    return new ui::StatisticsWindow(cont);
}

ui::SettingsWindow* WindowFactory::createSettingsWindow(controllers::SettingsController* cont) {
    return new ui::SettingsWindow(cont);
}


WindowFactory::WindowFactory() { }

WindowFactory::~WindowFactory() { }


} //framework
} // TF
