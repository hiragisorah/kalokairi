#include "player_movement.h"
#include "kalokairi.h"

PlayerMovement::PlayerMovement(void)
	: transform_(new Transform)
	, root_animation_(new Animation)
	, renderer_(nullptr)
{
}

void PlayerMovement::Initialize(void)
{
	this->renderer_ = this->owner()->Component<Renderer>();

	this->renderer_->animation()->SetAnimation("idle", 1);
	this->renderer_->animation()->SetAnimation(this->root_animation_, 0);

	this->root_animation_->frames_.resize(1);

	this->transform_->set_position(DirectX::Vector3(0, 0.72f, 0));
}

void PlayerMovement::Update(void)
{
	auto & transform = this->root_animation_->frames_[0].transforms_[0];

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

	float move_speed = 0.005f;

	this->transform_->RotateY(rot_side);
	this->transform_->MoveSide(move_side * move_speed * 0.5f);
	this->transform_->MoveForward(move_forward * move_speed);

	transform.position_ = this->transform_->position();
	transform.rotation_ = this->transform_->rotation();
	transform.scale_ = this->transform_->scale();

}

void PlayerMovement::Always(void)
{
}

void PlayerMovement::Finalize(void)
{
}
