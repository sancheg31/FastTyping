#pragma once

namespace FT::ui {

class LoginWindow;
class RegistrationWindow;
class AccountWindow;
class SettingsWindow;
class StatisticsWindow;

}

namespace FT {
namespace framework {

class WindowFactory
{

public:
    WindowFactory();
    ~WindowFactory();

    static ui::LoginWindow* createLoginWindow();
    static ui::RegistrationWindow* createRegistrationWindow();
    static ui::AccountWindow* createAccountWindow();
    static ui::StatisticsWindow* createStatisticsWindow();
    static ui::SettingsWindow* createSettingsWindow();

};

} //framework
} // TF
