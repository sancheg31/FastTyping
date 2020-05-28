#include "HorizontalInputBox.hpp"

namespace FT {
namespace ui {


HorizontalInputBox::HorizontalInputBox(const QString& labelText, const QString& lineText, const QRegExp& validator, QWidget* parent):
    InputBox(labelText, lineText, validator, parent), inLayout(new QHBoxLayout) {
    inLayout->addWidget(inLabel);
    inLayout->addWidget(inLine);
    inLayout->setSpacing(0);
    inLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(inLayout);
}

/*virtual*/ HorizontalInputBox::~HorizontalInputBox() { }

QHBoxLayout* HorizontalInputBox::layout() const {
    return inLayout;
}

/*virtual*/ void HorizontalInputBox::blocker() { }


} //ui
} //FT
