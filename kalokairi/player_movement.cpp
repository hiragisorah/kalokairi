#include "player_movement.h"
#include "kalokairi.h"
#include "camera.h"

PlayerMovement::PlayerMovement(void)
	: transform_(new Transform)
	, renderer_(nullptr)
{
}

void PlayerMovement::Initialize(void)
{
	this->renderer_ = this->owner()->Component<Renderer>();

	this->renderer_->animation()->SetAnimation("idle", 1);
	this->renderer_->animation()->SetIntercept(0, this->transform_, 0.9f);

	this->owner()->scene()->System<Camera>()->set_target(this->transform_);
}

void PlayerMovement::Update(void)
{
	auto walk_index = static_cast<int>(this->renderer_->animation()->animations("walk")->progress_);
	auto run_index = static_cast<int>(this->renderer_->animation()->animations("run")->progress_);

	float move_forward = static_cast<float>(Input::Press(Qt::Key_W)) - static_cast<float>(Input::Press(Qt::Key_S)) * 0.5f;

	float rot_side = static_cast<float>(Input::Press(Qt::Key_E)) - static_cast<float>(Input::Press(Qt::Key_Q));

	float move_speed = 0.03f;

	if (move_forward)
	{
		if (Input::Press(Qt::Key_Shift))
		{
			this->renderer_->animation()->SetAnimation("run", 1);
			move_speed *= (static_cast<float>(run_index % 2 == 1) + 1) * 3.f;
		}
		else
		{
			this->renderer_->animation()->SetAnimation("walk", 1);
			move_speed *= static_cast<float>(walk_index % 2 == 0);
		}
	}
	else
	{
		this->renderer_->animation()->SetAnimation("idle", 1);
	}

	this->transform_->RotateY(rot_side);
	this->transform_->MoveForward(move_forward * move_speed);
}

void PlayerMovement::Always(void)
{
}

void PlayerMovement::Finalize(void)
{
}

Transform * const PlayerMovement::transform(void)
{
	return this->transform_;
}
