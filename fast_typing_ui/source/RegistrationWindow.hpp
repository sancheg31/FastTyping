#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace FT {
namespace controllers {

class RegistrationController;

} //controllers
} //FT

namespace FT {
namespace ui {

class RegistrationWindow: public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RegistrationWindow)
public:
    RegistrationWindow(controllers::RegistrationController*, QWidget* parent = nullptr);
    virtual ~RegistrationWindow();

signals:
    void loginState();
    void loginState(const QString& login, const QString& password);

private slots:
    void slotConfirmButtonClicked();
    void slotLoginButtonClicked();

private:

    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::RegistrationController* controller;


};

} //ui
} //ft
