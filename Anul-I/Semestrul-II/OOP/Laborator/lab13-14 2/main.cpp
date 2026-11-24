#include "gui.h"
#include "tests.h"
#include <QApplication>
#include <QSpinBox>

#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);

	Validator val;
	RepoFile repo("activitati.txt");
	ListaActivitati lista;
	Service srv(repo, val, lista);
	GUI gui(srv);

	gui.show();

	return app.exec();
}