#pragma once

#include <QMainWindow>

namespace FT::controllers {

class AccountController;

}

namespace FT {
namespace ui {

class LoginWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LoginWindow)
public:
    LoginWindow(controllers::AccountController*, QWidget *parent = nullptr);
    virtual ~LoginWindow();

private slots:
    void slotConfirmClicked();

signals:
    void registerState();
    void mainState();

private:

    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::AccountController* controller;
};

} //ui
} //FT
