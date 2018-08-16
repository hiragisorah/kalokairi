#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QCloseEvent>
#include <QTimer>

#include "ui_kalokairi.h"
#include "..\graphics\graphics.h"
#include "..\frame-work\engine.h"

class Kalokairi : public QMainWindow
{
	Q_OBJECT

public:
	Kalokairi(QWidget *parent = Q_NULLPTR);

private:
	Ui::KalokairiClass ui_;
	QTimer * timer_;
	Seed::Graphics * graphics_;
	Seed::Engine * engine_;

	void closeEvent(QCloseEvent *event);

private slots:
	void Update(void);
};