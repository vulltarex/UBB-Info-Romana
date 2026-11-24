#include <QtWidgets/QApplication>

#include "repository.h"
#include "service.h"
#include "validator.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Repo repo("tractoare.txt");
    Validator val;
    Service srv(val, repo);
    GUI gui(srv);
    gui.show();
    return app.exec();
}
