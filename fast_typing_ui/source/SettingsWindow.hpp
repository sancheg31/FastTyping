#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace FT {
namespace ui {

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(SettingsWindow)
    Q_PROPERTY(QString ui_style READ currentStyle WRITE setCurrentStyle)
    Q_PROPERTY(QString ui_keyboard READ currentKeyboard WRITE setCurrentKeyboard)

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    virtual ~SettingsWindow() override;

    bool setCurrentStyle(const QString& styleName);
    bool setCurrentKeyboard(const QString& styleKeyboard);

    QString currentStyle() const;
    QString currentKeyboard() const;

signals:
    void styleChanged(const QString& styleName);
    void keyboardChanged(const QString& keyboardName);

private slots:
    void slotStyleChanged(int index);
    void slotKeyboardChanged(int index);

private:

    QStringList readStyleData() const;
    QStringList readKeyboardData() const;

    class Implementation;
    QScopedPointer<Implementation> impl;
};

} //ui
} //FT



