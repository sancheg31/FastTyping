#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace FT {
namespace ui {

class RegistrationWindow: public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RegistrationWindow)
public:
    RegistrationWindow(QWidget* parent = nullptr);
    virtual ~RegistrationWindow();

signals:
    void loginState();

private slots:
    void slotConfirmButtonClicked();
    void slotLoginButtonClicked();

private:
    bool isDataValid() const;

    class Implementation;
    QScopedPointer<Implementation> impl;


};

} //ui
} //ft
