#include "kalokairi.h"
#include "main_scene.h"

static std::unordered_map<Qt::Key, Input::KeyState> _keys;
static std::unordered_map<Qt::Key, bool> _new_keys;
static std::unordered_map<Qt::Key, bool> _old_keys;
static std::unordered_map<Qt::Key, unsigned int> _t_keys;

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
	Input::Update();

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

void Kalokairi::keyPressEvent(QKeyEvent * event)
{
	_new_keys[static_cast<Qt::Key>(event->key())] = true;
}

void Kalokairi::keyReleaseEvent(QKeyEvent * event)
{
	_new_keys[static_cast<Qt::Key>(event->key())] = false;
}

void Input::Update(void)
{
	for (auto & key : _new_keys)
	{
		auto & new_status = _new_keys[key.first];
		auto & old_status = _old_keys[key.first];
		auto & t_status = _t_keys[key.first];
		
		if(t_status) t_status++;

		if (t_status > 20)
			t_status = 0;

		if (!old_status && !new_status) _keys[key.first] = Input::KeyState::None;
		if (!old_status && new_status) _keys[key.first] = Input::KeyState::Trigger;
		if (old_status && new_status) _keys[key.first] = Input::KeyState::Press;
		if (old_status && !new_status) _keys[key.first] = Input::KeyState::Release;

		if (!old_status && new_status && t_status) _keys[key.first] = Input::KeyState::Repeat;
		if (!old_status && new_status) t_status = 1;

		old_status = new_status;
	}
}

bool Input::Trigger(const Qt::Key & key)
{
	return _keys[key] == Input::KeyState::Trigger || _keys[key] == Input::KeyState::Repeat;
}

bool Input::Release(const Qt::Key & key)
{
	return _keys[key] == Input::KeyState::Release;
}

bool Input::Repeat(const Qt::Key & key)
{
	return _keys[key] == Input::KeyState::Repeat;
}

bool Input::Press(const Qt::Key & key)
{
	return _keys[key] == Input::KeyState::Press;
}