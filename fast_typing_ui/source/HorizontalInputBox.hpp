#pragma once

#include "InputBox.hpp"

#include <QHBoxLayout>

namespace FT {
namespace ui {

class HorizontalInputBox: public InputBox
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(HorizontalInputBox)
    Q_PROPERTY(QHBoxLayout* ui_layout MEMBER inLayout READ layout)
public:
    HorizontalInputBox(const QString& labelText, const QString& lineText,
                     const QRegExp& validator, QWidget* parent = nullptr);
    virtual ~HorizontalInputBox();

    QHBoxLayout* layout() const;
protected:
    virtual void blocker() override;

    QHBoxLayout* inLayout;
};

} //ui
} //ft
