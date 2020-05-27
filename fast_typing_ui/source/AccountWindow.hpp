#pragma once

#include <QMainWindow>

class UserAccountInController;
class UserAccountOutController;

namespace FT {
namespace ui {


class AccountWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AccountWindow)
public:
    AccountWindow(UserAccountInController*, UserAccountOutController*, QWidget *parent = nullptr);
    virtual ~AccountWindow() override;

private slots:
    void toggleReadonly();

    void slotDataChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

    UserAccountInController* inController;
    UserAccountOutController* outController;
};


} //ui
} //FT



