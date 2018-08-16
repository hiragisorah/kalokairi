#include "engine.h"

Seed::Engine::Engine(Graphics & graphics)
	: graphics_(graphics)
	, current_scene_(nullptr)
	, next_scene_(nullptr)
	, pause_(false)
{
}

Seed::Engine::~Engine(void)
{
	if(this->current_scene_)
		delete this->current_scene_;
}

const bool Seed::Engine::Initialize(void)
{
	this->current_scene_->Initialize();

	return false;
}

void Seed::Engine::Pause(void)
{
	this->pause_ = true;
}

void Seed::Engine::Resume(void)
{
	this->pause_ = false;
}

Seed::Graphics * const Seed::Engine::graphics(void) const
{
	return &this->graphics_;
}

const bool Seed::Engine::Run(void)
{
	return ProcessScene();
}

const bool Seed::Engine::ProcessScene(void)
{
	if (this->current_scene_->IsAlive())
	{
		if (this->pause_)
		{
			this->current_scene_->Pause();
		}
		else
		{
			this->current_scene_->Update();
		}
		this->current_scene_->Always();

		this->current_scene_->Begin(this->graphics_);

		this->current_scene_->Render(this->graphics_);

		this->current_scene_->End(this->graphics_);
	}
	else
	{
		if (this->next_scene_)
		{
			this->current_scene_->Finalize();
			delete this->current_scene_;

			this->current_scene_ = this->next_scene_;
			this->next_scene_ = nullptr;

			this->current_scene_->Initialize();
		}
		else
		{
			this->current_scene_->Finalize();
			
			delete this->current_scene_;
			this->current_scene_ = nullptr;

			return false;
		}
	}

	return true;
}