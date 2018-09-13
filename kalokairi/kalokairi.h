#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_kalokairi.h"

class kalokairi : public QMainWindow
{
	Q_OBJECT

public:
	kalokairi(QWidget *parent = Q_NULLPTR);

private:
	Ui::kalokairiClass ui;
};
