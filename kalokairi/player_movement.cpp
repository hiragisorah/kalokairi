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
	auto anim_index = static_cast<int>(this->renderer_->animation()->animations("walk")->progress_);

	float move_side = static_cast<float>(Input::Press(Qt::Key_D)) - static_cast<float>(Input::Press(Qt::Key_A));

	float move_forward = static_cast<float>(Input::Press(Qt::Key_W)) - static_cast<float>(Input::Press(Qt::Key_S));

	float rot_side = static_cast<float>(Input::Press(Qt::Key_E)) - static_cast<float>(Input::Press(Qt::Key_Q));

	if (move_side || move_forward)
	{
		this->renderer_->animation()->SetAnimation("walk", 1);
	}
	else
	{
		this->renderer_->animation()->SetAnimation("idle", 1);
	}

	float move_speed = 0.03f * static_cast<float>(anim_index % 2 == 0);

	this->transform_->RotateY(rot_side);
	this->transform_->MoveSide(move_side * move_speed * 0.5f);
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
