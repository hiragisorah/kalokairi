#include "hierarchy-animation-editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	hierarchyanimationeditor w;
	w.show();
	return a.exec();
}
