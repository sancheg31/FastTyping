#pragma once

#include <QMainWindow>

namespace FT {
namespace ui {

class LoginWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LoginWindow)
public:
    LoginWindow(QWidget *parent = nullptr);
    virtual ~LoginWindow();

signals:
    void registerState();
    void mainState();

private:

    class Implementation;
    QScopedPointer<Implementation> impl;

};

} //ui
} //FT
