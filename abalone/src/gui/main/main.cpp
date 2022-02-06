#include <QApplication>

#include "view/mainwindow.h"
#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game model { };
    Controller controller { model };
    MainWindow w { model, controller };
    w.show();
    return a.exec();
}
