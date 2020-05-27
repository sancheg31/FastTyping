#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>

namespace FT {
namespace ui {

class InputBox: public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(InputBox)
    Q_PROPERTY(QLabel* ui_label MEMBER inLabel READ textLabel)
    Q_PROPERTY(QLineEdit* ui_line MEMBER inLine READ line NOTIFY inputTextChanged)
    Q_PROPERTY(QRegExpValidator* ui_validator MEMBER inValidator READ validator)

public:
    InputBox(const QString& text,
                const QString& line, const QRegExp& validator, QWidget* parent = nullptr);

    virtual~ InputBox();

    QLabel* textLabel() const;
    QLineEdit* line() const;
    QRegExpValidator* validator() const;

    void setLabelText(const QString& text);
    void setInputTextValidator(const QRegExp& validator);
    void setLineText(const QString& line);

signals:
    void inputTextChanged();

private slots:
    void slotInputTextChanged();

protected:
    virtual void blocker() = 0;

    QLabel* inLabel;
    QLineEdit* inLine;
    QRegExpValidator* inValidator;

};

} //ui
} //ft

