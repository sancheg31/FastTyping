#include "InputBox.hpp"


namespace FT {
namespace ui {


InputBox::InputBox(const QString& text, const QString& line, const QRegExp& validator, QWidget* parent) :
    QWidget(parent), inLabel(new QLabel(text)), inLine(new QLineEdit()), inValidator(new QRegExpValidator(validator))
{
    inLine->setPlaceholderText(line);
    if (validator.isValid())
        inLine->setValidator(inValidator);
    connect(inLine, SIGNAL(textChanged(const QString&)), SLOT(slotInputTextChanged()));
}

InputBox::~InputBox() { }

void InputBox::slotInputTextChanged() {
    if (inValidator->regExp().exactMatch(inLine->text()))
        emit inputTextChanged();
}

QLabel* InputBox::textLabel() const {
    return inLabel;
}

QLineEdit* InputBox::line() const {
    return inLine;
}

QRegExpValidator* InputBox::validator() const {
    return inValidator;
}

void InputBox::setLabelText(const QString& text) {
    inLabel->setText(text);
}

void InputBox::setInputTextValidator(const QRegExp& validator) {
    inValidator->setRegExp(validator);
}

void InputBox::setLineText(const QString& line) {
    inLine->setPlaceholderText(line);
}


} //ui
} //FT
