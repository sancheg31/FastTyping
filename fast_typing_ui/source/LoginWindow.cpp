


#include "LoginWindow.hpp"

#include <QLabel>
#include <QPushButton>


#include "HorizontalInputBox.hpp"
#include "VerticalInputBox.hpp"
#include "TextValidatorContainer.hpp"

namespace FT {
namespace ui {

class LoginWindow::Implementation
{
public:
    Implementation(LoginWindow* obj): parent(obj) {

        titleLabel->setFont(QFont("Arial", 48, 2));
        titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        loginBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        auto sizePolicy = loginBox->sizePolicy();

        passwordBox->setSizePolicy(sizePolicy);
        passwordBox->line()->setEchoMode(QLineEdit::Password);

        confirmButton->setSizePolicy(sizePolicy);
        confirmButton->setFixedSize(150, 30);

        QObject::connect(confirmButton, &QPushButton::clicked, parent, &LoginWindow::mainState);
        QObject::connect(registerButton, &QPushButton::clicked, parent, &LoginWindow::registerState);
    }

    LoginWindow* parent;

    QLabel* titleLabel{new QLabel(tr("FAST TYPING"))};
    QLabel* incorrectDataLabel{new QLabel()};

    VerticalInputBox* loginBox{new VerticalInputBox(tr("login:"), "",
                                data::TextValidatorContainer::getValidator("login"))};

    VerticalInputBox* passwordBox{new VerticalInputBox(tr("password:"), "",
                                    data::TextValidatorContainer::getValidator("password"))};

    QPushButton* confirmButton{new QPushButton(tr("Confirm"))};

    QLabel* registerLabel{new QLabel(tr("No account? Register:"))};
    QPushButton* registerButton{new QPushButton(tr("Register"))};

};

LoginWindow::LoginWindow(QWidget *parent): QMainWindow(parent) {
    impl.reset(new Implementation(this));


    QVBoxLayout* l = new QVBoxLayout();
    QVBoxLayout* boxes = new QVBoxLayout();
    l->addWidget(impl->titleLabel, Qt::AlignCenter);
    boxes->addWidget(impl->incorrectDataLabel);
    boxes->addWidget(impl->loginBox);
    boxes->addWidget(impl->passwordBox);
    boxes->setSpacing(1);

    QVBoxLayout* loginl = new QVBoxLayout();
    loginl->addWidget(impl->registerLabel);
    loginl->addWidget(impl->registerButton);
    loginl->setSpacing(1);

    QHBoxLayout* hl = new QHBoxLayout();
    hl->addLayout(boxes);
    hl->addLayout(loginl);
    hl->setAlignment(boxes, Qt::AlignTop | Qt::AlignLeft);
    hl->setAlignment(loginl, Qt::AlignHCenter | Qt::AlignTop);

    l->addLayout(hl);

    QVBoxLayout* confirml = new QVBoxLayout();
    confirml->addWidget(impl->confirmButton);
    l->addLayout(confirml);
    l->setAlignment(confirml, Qt::AlignHCenter);
    l->setSpacing(2);

    QWidget* w = new QWidget();
    w->setLayout(l);

    setWindowTitle("login");
    setCentralWidget(w);

    setFixedSize(620, 400);

}

/*virtual*/ LoginWindow::~LoginWindow() { }


} //ui
} //FT

