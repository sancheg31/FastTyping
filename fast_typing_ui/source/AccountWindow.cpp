
#include "AccountWindow.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "VerticalInputBox.hpp"
#include "HorizontalInputBox.hpp"

#include "controllers/AccountController.hpp"
#include "TextValidatorContainer.hpp"

namespace FT {
namespace ui {


class AccountWindow::Implementation
{
public:
    Implementation(AccountWindow* obj): parent(obj) {

        parent->controller->loadAccountData("onono", "Computer784");
        loginBox->line()->setText(parent->controller->login());
        emailBox->line()->setText(parent->controller->email());
        passwordBox->line()->setText(parent->controller->password());

        titleLabel->setFont(QFont("Calibri", 20, 4, 0));
        titleLabel->setWordWrap(true);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setFixedSize(750, 100);

        loginBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        auto sizePolicy = loginBox->sizePolicy();
        loginBox->line()->setReadOnly(true);
        loginBox->line()->setFixedSize(400, 25);

        emailBox->setSizePolicy(sizePolicy);
        emailBox->line()->setReadOnly(true);
        emailBox->line()->setFixedSize(400, 25);

        passwordBox->setSizePolicy(sizePolicy);
        passwordBox->line()->setReadOnly(true);
        passwordBox->line()->setFixedSize(400, 25);

        editButton->setFixedSize(100, 25);
        saveButton->setFixedSize(100, 25);

        QObject::connect(editButton, SIGNAL(clicked()), parent, SLOT(toggleReadonly()));
        QObject::connect(saveButton, SIGNAL(clicked()), parent, SLOT(slotDataChanged()));

    }

    AccountWindow* parent;
    QLabel* titleLabel{new QLabel("Welcome to your user account.\n"
                                  "Here you can change your personal information")};

    QLabel* incorrectDataLabel{new QLabel()};

    VerticalInputBox* loginBox{new VerticalInputBox(tr("login:"), "",
                                data::TextValidatorContainer::getValidator("login"))};

    VerticalInputBox* emailBox{new VerticalInputBox(tr("email:"), "",
                                data::TextValidatorContainer::getValidator("email"))};

    VerticalInputBox* passwordBox{new VerticalInputBox(tr("password:"), "",
                                data::TextValidatorContainer::getValidator("password"))};

    QPushButton* editButton{new QPushButton("Edit")};
    QPushButton* saveButton{new QPushButton(tr("Save"))};

    QString oldLogin;
    QString oldEmail;
    QString oldPassword;


    void saveState() {
        oldLogin = loginBox->line()->text();
        oldPassword = passwordBox->line()->text();
        oldEmail = emailBox->line()->text();
    }

    void toggleReadOnly() {
        loginBox->line()->setReadOnly(!loginBox->line()->isReadOnly());
        emailBox->line()->setReadOnly(!emailBox->line()->isReadOnly());
        passwordBox->line()->setReadOnly(!passwordBox->line()->isReadOnly());
    }


};


AccountWindow::AccountWindow(controllers::AccountController* cont,
                             QWidget* parent): QMainWindow(parent), controller(cont) {

    impl.reset(new Implementation(this));

    QVBoxLayout* mainl = new QVBoxLayout();

    mainl->addWidget(impl->titleLabel, Qt::AlignCenter);
    mainl->addWidget(impl->incorrectDataLabel, Qt::AlignLeft);
    mainl->addWidget(impl->loginBox, Qt::AlignLeft);
    impl->loginBox->layout()->setSpacing(4);
    mainl->addWidget(impl->emailBox, Qt::AlignLeft);
    impl->emailBox->layout()->setSpacing(4);
    mainl->addWidget(impl->passwordBox, Qt::AlignLeft);
    impl->passwordBox->layout()->setSpacing(4);
    mainl->setSizeConstraint(QLayout::SetFixedSize);
    mainl->setSpacing(6);

    QHBoxLayout* buttonl = new QHBoxLayout();
    buttonl->addWidget(impl->saveButton);
    buttonl->addWidget(impl->editButton);
    buttonl->setSizeConstraint(QLayout::SetFixedSize);
    buttonl->setSpacing(6);
    buttonl->setContentsMargins(0, 0, 0, 0);

    QWidget* dummy = new QWidget();
    dummy->setLayout(buttonl);

    mainl->addWidget(dummy, Qt::AlignLeft);
    mainl->setContentsMargins(15, 15, 15, 30);

    QWidget* w = new QWidget();
    w->setLayout(mainl);
    setCentralWidget(w);
}

AccountWindow::~AccountWindow() { }

void AccountWindow::toggleReadonly() {
    if (impl->loginBox->line()->isReadOnly()) {
        impl->saveState();
        impl->toggleReadOnly();
    }
}

void AccountWindow::slotDataChanged() {
    impl->toggleReadOnly();
    bool changed = false;
    if (impl->loginBox->line()->text() != impl->oldLogin) {
        qDebug() << "old login: " << impl->oldLogin <<
                    "new login: " << impl->loginBox->line()->text();
        controller->updateLogin(impl->loginBox->line()->text());
        changed = true;
    }
    if (impl->emailBox->line()->text() != impl->oldEmail) {
        qDebug() << "old email: " << impl->oldEmail <<
                    "new email: " << impl->emailBox->line()->text();
        controller->updateEmail(impl->emailBox->line()->text());
        changed = true;
    }
    if (impl->passwordBox->line()->text() != impl->oldPassword) {
        qDebug() << "old password: " << impl->oldPassword <<
                    "new password: " << impl->passwordBox->line()->text();
        controller->updatePassword(impl->passwordBox->line()->text());
        changed = true;
    }
    if (changed)
        emit accountDataChanged();
}

} //ui
} //FT
