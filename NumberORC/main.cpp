#include "numberorc.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NumberORC w;
	w.show();
	return a.exec();
}
