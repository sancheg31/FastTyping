#pragma once

#include <QMainWindow>


namespace FT {
namespace controllers {

class AccountController;

} //controllers
} //FT

namespace FT {
namespace ui {


class AccountWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AccountWindow)
public:
    AccountWindow(controllers::AccountController*, QWidget *parent = nullptr);
    virtual ~AccountWindow() override;

private slots:
    void toggleReadonly();
    void slotDataChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::AccountController* controller;
};


} //ui
} //FT



