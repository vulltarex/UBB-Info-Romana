#include <QApplication>
#include "GUI.h"
#include "tests.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    testAll();
    Repo repo("studenti.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return app.exec();
}