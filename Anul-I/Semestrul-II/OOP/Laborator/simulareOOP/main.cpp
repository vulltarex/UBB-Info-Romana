#include <QtWidgets/QApplication>
#include "gui.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testInstrument();
    testRepoService();
    Repo repo("instrumente.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return app.exec();
}
