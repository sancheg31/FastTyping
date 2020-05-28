
#include "WindowFactory.hpp"


#include "AccountWindow.hpp"
#include "LoginWindow.hpp"
#include "StatisticsWindow.hpp"
#include "RegistrationWindow.hpp"
#include "SettingsWindow.hpp"

namespace FT {
namespace framework {


ui::LoginWindow* WindowFactory::createLoginWindow() {
    return new ui::LoginWindow();
}

ui::RegistrationWindow* WindowFactory::createRegistrationWindow() {
    return new ui::RegistrationWindow();
}

ui::AccountWindow* WindowFactory::createAccountWindow() {
    return new ui::AccountWindow(nullptr, nullptr);
}

ui::StatisticsWindow* WindowFactory::createStatisticsWindow() {
    return new ui::StatisticsWindow(nullptr);
}

ui::SettingsWindow* WindowFactory::createSettingsWindow() {
    return new ui::SettingsWindow(nullptr);
}


WindowFactory::WindowFactory() { }

WindowFactory::~WindowFactory() { }


} //framework
} // TF
