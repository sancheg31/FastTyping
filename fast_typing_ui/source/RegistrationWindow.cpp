
#include "RegistrationWindow.hpp"

#include <QPushButton>

#include "VerticalInputBox.hpp"
#include "TextValidatorContainer.hpp"


namespace FT {
namespace ui {

class RegistrationWindow::Implementation
{
public:
    Implementation(RegistrationWindow* obj): parent(obj) {
        titleLabel->setFont(QFont("Arial", 48, 2));
        titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);


        loginBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        auto sizePolicy = loginBox->sizePolicy();
        loginBox->line()->setMaxLength(50);

        emailBox->line()->setMaxLength(50);
        emailBox->setSizePolicy(sizePolicy);

        passwordBox->line()->setMaxLength(50);
        passwordBox->line()->setEchoMode(QLineEdit::Password);
        passwordBox->setSizePolicy(sizePolicy);

        confirmPasswordBox->line()->setMaxLength(50);
        confirmPasswordBox->line()->setEchoMode(QLineEdit::Password);
        confirmPasswordBox->setSizePolicy(sizePolicy);


        confirmRegButton->setSizePolicy(sizePolicy);
        confirmRegButton->setFixedSize(150, 30);

        QObject::connect(confirmRegButton, SIGNAL(clicked()), parent, SLOT(slotConfirmButtonClicked()));
        QObject::connect(loginAccountButton, SIGNAL(clicked()), parent, SLOT(slotLoginButtonClicked()));
    }

    RegistrationWindow* parent;

    QLabel* titleLabel{new QLabel(tr("FAST TYPING"))};
    QLabel* incorrectData{new QLabel()};

    VerticalInputBox* loginBox{new VerticalInputBox(tr("login:"), "",
                                                    data::TextValidatorContainer::getValidator("login"))};

    VerticalInputBox* emailBox{new VerticalInputBox(tr("email:"), "",
                                                    data::TextValidatorContainer::getValidator("email"))};

    VerticalInputBox* passwordBox{new VerticalInputBox( tr("password:"),
                                                        tr("at least 7 characters"),
                                                        data::TextValidatorContainer::getValidator("password"))};

    VerticalInputBox* confirmPasswordBox{new VerticalInputBox(tr("confirm password:"),
                                                              tr("at least 7 characters"),
                                                              data::TextValidatorContainer::getValidator("password"))};

    QPushButton* confirmRegButton{new QPushButton(tr("Confirm"))};

    QLabel* hasAccountLabel{new QLabel(tr("Has account? Login in:"))};

    QPushButton* loginAccountButton{new QPushButton(tr("Login"))};

};


RegistrationWindow::RegistrationWindow(QWidget* parent): QMainWindow(parent) {
    impl.reset(new Implementation(this));

    QVBoxLayout* l = new QVBoxLayout();
    QVBoxLayout* boxes = new QVBoxLayout();
    l->addWidget(impl->titleLabel, Qt::AlignCenter);
    boxes->addWidget(impl->incorrectData);
    boxes->addWidget(impl->loginBox);
    boxes->addWidget(impl->emailBox);
    boxes->addWidget(impl->passwordBox);
    boxes->addWidget(impl->confirmPasswordBox);
    boxes->setSpacing(1);

    QVBoxLayout* loginl = new QVBoxLayout();
    loginl->addWidget(impl->hasAccountLabel);
    loginl->addWidget(impl->loginAccountButton);
    loginl->setSpacing(1);

    QHBoxLayout* hl = new QHBoxLayout();
    hl->addLayout(boxes);
    hl->addLayout(loginl);
    hl->setAlignment(boxes, Qt::AlignVCenter | Qt::AlignLeft);
    hl->setAlignment(loginl, Qt::AlignCenter);

    l->addLayout(hl);

    QVBoxLayout* confirml = new QVBoxLayout();
    confirml->addWidget(impl->confirmRegButton);
    l->addLayout(confirml);
    l->setAlignment(confirml, Qt::AlignHCenter);
    l->setSpacing(2);

    QWidget* w = new QWidget();
    w->setLayout(l);

    setWindowTitle("Registration");
    setCentralWidget(w);

    setFixedSize(620, 400);
}

/*virtual*/ RegistrationWindow::~RegistrationWindow() { }

bool RegistrationWindow::isDataValid() const {
    return false;
}

void RegistrationWindow::slotConfirmButtonClicked() {
    //if (isDataValid())
        emit loginState();
}

void RegistrationWindow::slotLoginButtonClicked() {
    emit loginState();
}

} //ui
} //FT
