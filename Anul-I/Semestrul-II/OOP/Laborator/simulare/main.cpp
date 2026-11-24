#include "gui.h"
#include "tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testAutomobil();
    testRepoService();
    Repo repo("automobile.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return app.exec();
}
