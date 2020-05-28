

#include "MainWindow.hpp"

#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FT::ui::MainWindow* m = new FT::ui::MainWindow;
    m->show();
    return app.exec();
}
