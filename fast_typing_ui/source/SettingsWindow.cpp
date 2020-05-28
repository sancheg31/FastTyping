
#include "SettingsWindow.hpp"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include <algorithm>

#include "controllers/SettingsController.hpp"


namespace FT {
namespace ui {


class SettingsWindow::Implementation
{
public:
    Implementation(SettingsWindow* obj): parent(obj)  {

        styleLabel->setFont(QFont("Calibri", 12, 2));
        layoutLabel->setFont(styleLabel->font());

        styleBox->setFont(QFont("Calibri", 10, 3));
        layoutBox->setFont(styleBox->font());

        QStringList data = loadStyleData();
        std::for_each(data.begin(), data.end(), [this](const QString& text) {
            styleBox->addItem(text);

        });

        data = loadLayoutData();
        std::for_each(data.begin(), data.end(), [this](const QString& text) {
           layoutBox->addItem(text);
        });

        styleBox->setEditable(false);
        styleBox->setDuplicatesEnabled(false);

        layoutBox->setEditable(false);
        layoutBox->setDuplicatesEnabled(false);

        QObject::connect(styleBox, SIGNAL(currentIndexChanged(int)),
                            parent, SLOT(slotStyleChanged(int)));
        QObject::connect(layoutBox, SIGNAL(currentIndexChanged(int)),
                            parent, SLOT(slotLayoutChanged(int)));
    }

    SettingsWindow* parent;
    QComboBox* styleBox{new QComboBox()};
    QLabel* styleLabel{new QLabel("Change application style:")};
    QComboBox* layoutBox{new QComboBox()};
    QLabel* layoutLabel{new QLabel("Change language layout:")};


    QStringList loadStyleData() {
        return parent->controller->styles();
    }

    QStringList loadLayoutData() {
        return parent->controller->layouts();
    }

};

void SettingsWindow::slotStyleChanged(int index) {
    controller->setCurrentStyle(impl->styleBox->itemText(index));
    emit styleChanged(impl->styleBox->itemText(index));
}

void SettingsWindow::slotLayoutChanged(int index) {
    controller->setCurrentLayout(impl->layoutBox->itemText(index));
    emit layoutChanged(impl->layoutBox->itemText(index));
}


SettingsWindow::SettingsWindow(controllers::SettingsController* cont,
                               QWidget* parent): QMainWindow(parent), controller(cont) {
    impl.reset(new Implementation(this));

    QGridLayout* l = new QGridLayout;
    l->addWidget(impl->styleLabel, 0, 0, 1, 2);
    l->addWidget(impl->styleBox, 0, 2, 1, 3);
    l->addWidget(impl->layoutLabel, 1, 0, 1, 2);
    l->addWidget(impl->layoutBox, 1, 2, 1, 3);

    l->setHorizontalSpacing(20);
    l->setVerticalSpacing(5);
    l->setContentsMargins(15, 20, 0, 0);
    l->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    impl->styleBox->setFixedSize(140, 30);
    impl->layoutBox->setFixedSize(140, 30);

    QWidget* w = new QWidget();

    w->setLayout(l);
    w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCentralWidget(w);
}

SettingsWindow::~SettingsWindow() { }



} //ui
} //FT
