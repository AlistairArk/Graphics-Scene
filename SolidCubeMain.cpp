#include <QApplication>
#include <QVBoxLayout>
#include "SolidCubeWindow.h"

int main(int argc, char *argv[]){

	// create the application
	QApplication app(argc, argv);

	// create a master widget
    SolidCubeWindow *window = new SolidCubeWindow(NULL);

	// resize the window
	window->resize(1100, 720);

	// show the label
	window->show();

	// start it running
	app.exec();

	// clean up
	//	delete controller;
	delete window;

	// return to caller
	return 0;
}
