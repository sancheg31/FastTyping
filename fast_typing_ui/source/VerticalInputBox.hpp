#pragma once

#include <QWidget>

#include "InputBox.hpp"

#include <QVBoxLayout>

namespace FT {
namespace ui {

class VerticalInputBox: public InputBox
{

    Q_OBJECT
    Q_DISABLE_COPY_MOVE(VerticalInputBox)
    Q_PROPERTY(QVBoxLayout* ui_layout MEMBER inLayout READ layout)
public:
    VerticalInputBox(const QString& labelText, const QString& lineText,
                     const QRegExp& validator, QWidget* parent = nullptr);
    virtual ~VerticalInputBox();

    QVBoxLayout* layout() const;

protected:
    virtual void blocker() override;

    QVBoxLayout* inLayout;
};

} //ui
} //ft
