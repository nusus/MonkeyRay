#include "stdafx.h"
#include "monkeyraygui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MonkeyRayGUI w;
	w.show();
	return a.exec();
}
