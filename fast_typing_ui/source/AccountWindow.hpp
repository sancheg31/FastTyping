#pragma once

#include <QMainWindow>

namespace FT {
namespace controllers {

class AccountInController;
class AccountOutController;

} //controllers
} //FT

namespace FT {
namespace ui {


class AccountWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AccountWindow)
public:
    AccountWindow(controllers::AccountInController*,
                  controllers::AccountOutController*, QWidget *parent = nullptr);
    virtual ~AccountWindow() override;

private slots:
    void toggleReadonly();

    void slotDataChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    controllers::AccountInController* inController;
    controllers::AccountOutController* outController;
};


} //ui
} //FT



