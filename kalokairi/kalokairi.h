#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QCloseEvent>
#include <QTimer>

#include "ui_kalokairi.h"
#include "..\graphics\graphics.h"
#include "..\frame-work\engine.h"

namespace Input
{
	enum class KeyState
	{
		None,
		Trigger,
		Press,
		Release,
		Repeat,
	};

	void Update(void);
	bool Trigger(const Qt::Key & key);
	bool Release(const Qt::Key & key);
	bool Repeat(const Qt::Key & key);
	bool Press(const Qt::Key & key);
}

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

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private slots:
	void Update(void);
};