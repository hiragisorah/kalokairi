#include "kalokairi.h"
#include "main_scene.h"

Kalokairi::Kalokairi(QWidget *parent)
	: QMainWindow(parent)
{
	this->ui_.setupUi(this);
	
	this->setFixedSize(this->size());

	this->show();

	auto & widget = this->ui_.centralWidget;

	auto handle = reinterpret_cast<void*>(widget->winId());
	auto width = widget->width();
	auto height = widget->height();

	this->graphics_ = new Seed::Graphics();
	this->engine_ = new Seed::Engine(*this->graphics_);

	this->graphics_->Initialize(handle, width, height);
	this->engine_->Initialize<MainScene>();

	this->timer_ = new QTimer(this);
	connect(this->timer_, SIGNAL(timeout()), this, SLOT(Update()));
	this->timer_->start(1000 / 60);
}

void Kalokairi::Update(void)
{
	if (!this->engine_->Run())
	{
		this->timer_->stop();

		this->graphics_->Finalize();

		delete this->graphics_;
		delete this->engine_;

		qApp->exit();
	}
}

void Kalokairi::closeEvent(QCloseEvent * event)
{
	int res = QMessageBox::question(this, QString::fromLocal8Bit("確認"), QString::fromLocal8Bit("終了しますか？"));

	if (res == QMessageBox::No)
	{
		event->ignore();
	}
	if(res == QMessageBox::Yes)
	{
		this->timer_->stop();

		this->graphics_->Finalize();

		delete this->graphics_;
		delete this->engine_;
	}
}