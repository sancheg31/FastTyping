#include "VerticalInputBox.hpp"



namespace FT {
namespace ui {


VerticalInputBox::VerticalInputBox(const QString& labelText, const QString& lineText, const QRegExp& validator, QWidget* parent):
    InputBox(labelText, lineText, validator, parent), inLayout(new QVBoxLayout) {
    inLayout->addWidget(inLabel);
    inLayout->addWidget(inLine);
    inLayout->setSpacing(2);
    setLayout(inLayout);
}

/*virtual*/ VerticalInputBox::~VerticalInputBox() { }

QVBoxLayout* VerticalInputBox::layout() const {
    return inLayout;
}

/*virtual*/ void VerticalInputBox::blocker() { }


} //ui
} //FT
