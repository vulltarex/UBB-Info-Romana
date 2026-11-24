#include "lab1011qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    lab1011qt window;
    window.show();
    return app.exec();
}
