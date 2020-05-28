
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
        saveButton->setDisabled(true);

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

    connect(controller, SIGNAL(loginChanged(QString, QString)), this, SLOT(slotLoginChanged(QString)));
    connect(controller, SIGNAL(emailChanged(QString, QString)), this, SLOT(slotEmailChanged(QString)));
    connect(controller, SIGNAL(passwordChanged(QString, QString)), this, SLOT(slotPasswordChanged(QString)));

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
        impl->saveButton->setEnabled(true);
    }
}

void AccountWindow::slotDataChanged() {

    impl->toggleReadOnly();
    bool changed = false;

    if (impl->loginBox->line()->text() != impl->oldLogin) {

        qDebug() << "old login: " << impl->oldLogin <<
                    "new login: " << impl->loginBox->line()->text();

        bool updated = controller->updateLogin(impl->loginBox->line()->text());

        if (!updated) {
            impl->loginBox->line()->setText(impl->oldLogin);
        }
        changed = changed | updated;

    }

    if (impl->emailBox->line()->text() != impl->oldEmail) {

        qDebug() << "old email: " << impl->oldEmail <<
                    "new email: " << impl->emailBox->line()->text();

        bool updated = controller->updateEmail(impl->emailBox->line()->text());
        if (!updated) {
            impl->emailBox->line()->setText(impl->oldEmail);
        }
        changed = changed | updated;
    }
    if (impl->passwordBox->line()->text() != impl->oldPassword) {

        qDebug() << "old password: " << impl->oldPassword <<
                    "new password: " << impl->passwordBox->line()->text();

        bool updated = controller->updatePassword(impl->passwordBox->line()->text());

        if (!updated) {
            impl->passwordBox->line()->setText(impl->oldPassword);
        }
        changed = changed | updated;
    }

    if (changed)
        emit accountDataChanged();
    impl->saveButton->setDisabled(true);
}

void AccountWindow::slotLoginChanged(const QString& newLogin) {
    impl->oldLogin = newLogin;
    impl->loginBox->line()->setText(newLogin);
}

void AccountWindow::slotEmailChanged(const QString& newEmail) {
    impl->oldEmail = newEmail;
    impl->emailBox->line()->setText(newEmail);
}

void AccountWindow::slotPasswordChanged(const QString& newPassword) {
    impl->oldPassword = newPassword;
    impl->passwordBox->line()->setText(newPassword);
}

} //ui
} //FT
