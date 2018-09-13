#include "kalokairi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	kalokairi w;
	w.show();
	return a.exec();
}
