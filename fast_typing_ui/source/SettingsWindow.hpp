#pragma once

#include <QMainWindow>
#include <QScopedPointer>


namespace FT {
namespace controllers {

class SettingsController;

} //controllers
} //FT

namespace FT {
namespace ui {

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(SettingsWindow)
public:
    explicit SettingsWindow(controllers::SettingsController*, QWidget *parent = nullptr);
    virtual ~SettingsWindow() override;

signals:
    void styleChanged(const QString& styleName);
    void layoutChanged(const QString& keyboardName);

private slots:
    void slotStyleChanged(int index);
    void slotLayoutChanged(int index);

private:

    controllers::SettingsController* controller;

    class Implementation;
    QScopedPointer<Implementation> impl;
};

} //ui
} //FT



