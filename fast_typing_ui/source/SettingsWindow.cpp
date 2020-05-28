
#include "SettingsWindow.hpp"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include <algorithm>

namespace FT {
namespace ui {


class SettingsWindow::Implementation
{
public:
    Implementation(SettingsWindow* obj): parent(obj)  {

        styleLabel->setFont(QFont("Calibri", 12, 2));
        keyboardLabel->setFont(styleLabel->font());

        styleBox->setFont(QFont("Calibri", 10, 3));
        keyboardBox->setFont(styleBox->font());

        QStringList data = parent->readStyleData();
        std::for_each(data.begin(), data.end(), [this](const QString& text) {
            styleBox->addItem(text);

        });

        data = parent->readKeyboardData();
        std::for_each(data.begin(), data.end(), [this](const QString& text) {
           keyboardBox->addItem(text);
        });

        styleBox->setEditable(false);
        styleBox->setDuplicatesEnabled(false);

        keyboardBox->setEditable(false);
        keyboardBox->setDuplicatesEnabled(false);

        QObject::connect(styleBox, SIGNAL(currentIndexChanged(int)),
                            parent, SLOT(slotStyleChanged(int)));
        QObject::connect(keyboardBox, SIGNAL(currentIndexChanged(int)),
                            parent, SLOT(slotKeyboardChanged(int)));
    }

    SettingsWindow* parent;
    QComboBox* styleBox{new QComboBox()};
    QLabel* styleLabel{new QLabel("Change application style:")};
    QComboBox* keyboardBox{new QComboBox()};
    QLabel* keyboardLabel{new QLabel("Change keyboard layout:")};

};

QStringList SettingsWindow::readStyleData() const {
    return {("Windows"), ("MacOS")};
}

QStringList SettingsWindow::readKeyboardData() const {
    return {("English"), ("Russian"), ("Ukrainian")};
}

void SettingsWindow::slotStyleChanged(int index) {
    emit styleChanged(impl->styleBox->itemText(index));
}

void SettingsWindow::slotKeyboardChanged(int index) {
    emit keyboardChanged(impl->keyboardBox->itemText(index));
}

bool SettingsWindow::setCurrentStyle(const QString& styleName) {
    if (int index = impl->styleBox->findText(styleName) != -1) {
        impl->styleBox->setCurrentIndex(index);
        return true;
    }
    return false;
}

bool SettingsWindow::setCurrentKeyboard(const QString& keyboardName) {
    if (int index = impl->keyboardBox->findText(keyboardName) != -1) {
        impl->keyboardBox->setCurrentIndex(index);
        return true;
    }
    return false;
}

QString SettingsWindow::currentStyle() const {
    return impl->styleBox->itemText(impl->styleBox->currentIndex());
}

QString SettingsWindow::currentKeyboard() const {
    return impl->keyboardBox->itemText(impl->keyboardBox->currentIndex());
}


SettingsWindow::SettingsWindow(controllers::SettingsController* cont,
                               QWidget* parent): QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));

    QGridLayout* l = new QGridLayout;
    l->addWidget(impl->styleLabel, 0, 0, 1, 2);
    l->addWidget(impl->styleBox, 0, 2, 1, 3);
    l->addWidget(impl->keyboardLabel, 1, 0, 1, 2);
    l->addWidget(impl->keyboardBox, 1, 2, 1, 3);

    l->setHorizontalSpacing(20);
    l->setVerticalSpacing(5);
    l->setContentsMargins(15, 20, 0, 0);
    l->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    impl->styleBox->setFixedSize(140, 30);
    impl->keyboardBox->setFixedSize(140, 30);

    //Push button to check and adjust sizes
    /*QPushButton* p  = new QPushButton();
    connect(p, &QPushButton::clicked, [this]() {
        qDebug() << impl->styleLabel->size();
        qDebug() << impl->styleBox->size();
        qDebug() << impl->keyboardLabel->size();
        qDebug() << impl->keyboardBox->size();
    });
    l->addWidget(p, 2, 0, 1, 1);*/

    QWidget* w = new QWidget();

    w->setLayout(l);
    w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCentralWidget(w);
}

SettingsWindow::~SettingsWindow() { }



} //ui
} //FT
