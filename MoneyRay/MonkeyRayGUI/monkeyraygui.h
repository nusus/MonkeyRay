#ifndef MONKEYRAYGUI_H
#define MONKEYRAYGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_monkeyraygui.h"

class MonkeyRayGUI : public QMainWindow
{
	Q_OBJECT

public:
	MonkeyRayGUI(QWidget *parent = 0);
	~MonkeyRayGUI();

private:
	Ui::MonkeyRayGUIClass ui;
};

#endif // MONKEYRAYGUI_H
