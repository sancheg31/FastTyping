#pragma once

#include <QMainWindow>
#include "LoginWindow.hpp"
#include "RegistrationWindow.hpp"

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
    void slotMainWindow();

};

} //ui
} //FT

