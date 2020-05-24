
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QDateTime>

#include <algorithm>
#include <iterator>

#include "MainWindow.hpp"
#include "DatabaseModel.hpp"



int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto & inst = FT::data::DatabaseModel::instance();
    auto rows = inst.selectRows("SELECT login, email, password, created_at FROM Account");
    auto list = rows.value();

    for (int i = 0; i < list.size(); ++i) {
        qDebug() << i + 1 << '.';
        qDebug() << "\tlogin: " << list[i][0].toString();
        qDebug() << "\temail: " << list[i][1].toString();
        qDebug() << "\tpassword: " << list[i][2].toString();
        qDebug() << "\tdate: " << list[i][3].toString();
    }

    return a.exec();
}
