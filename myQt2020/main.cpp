#include "myqt2020.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	myQt2020 w;
	w.show();
	return a.exec();
}
