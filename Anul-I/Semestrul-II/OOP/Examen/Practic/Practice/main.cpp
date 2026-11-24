#include <QApplication>
#include "gui.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Repo repo("masini.txt");
    Service srv(repo);
    GUI gui(srv);
    gui.show();
    return app.exec();
}