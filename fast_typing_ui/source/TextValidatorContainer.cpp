
#include "TextValidatorContainer.hpp"


#include <QDebug>
#include <QString>
#include <QRegExp>
#include <QHash>


namespace FT {
namespace data {

class TextValidatorContainer::Implementation
{
public:
    Implementation(TextValidatorContainer* obj): parent(obj) {
        QString loginKey("login");
        QString loginValue("([A-Za-z](?:[A-Za-z0-9_]{0,49}))");
        assert(QRegExp(loginValue).isValid());
        cont.insert(loginKey, loginValue);

        QString emailKey("email");
        QString emailValue("([A-Za-z0-9_]+(\\.[A-Za-z0-9_])*\\.@[A-Za-z0-9_]+(\\.[A-Za-z0-9_])+)");
        assert(QRegExp(emailValue).isValid());
        cont.insert(emailKey, emailValue);

        QString passwordKey("password");
        QString passwordValue("((?:[A-za-z0-9\\$%\\^&\\*_\\.]){7,50})");
        assert(QRegExp(passwordValue).isValid());
        cont.insert(passwordKey, passwordValue);
    }

    TextValidatorContainer* parent;
    QHash<QString, QString> cont;
};

/*static*/ QRegExp TextValidatorContainer::getValidator(const QString& key) {
    return QRegExp(instance().impl->cont.value(key));
}

/*static*/ bool TextValidatorContainer::addValidator(const QString& key, const QString& value) {
    if (QRegExp(value).isValid() && instance().impl->cont.find(key) != instance().impl->cont.end()) {
        instance().impl->cont.insert(key, value);
        return true;
    }
    return false;
}

/*static*/ TextValidatorContainer& TextValidatorContainer::instance() {
    static TextValidatorContainer inst;
    return inst;
}

TextValidatorContainer::TextValidatorContainer() {
    impl.reset(new Implementation(this));
}


} //data
} //FT
