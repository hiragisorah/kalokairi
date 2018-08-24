#include "stage_event.h"

StageEvent::StageEvent(void)
	: transform_(new Transform)
{
}

StageEvent::~StageEvent(void)
{
	delete this->transform_;
}

void StageEvent::Initialize(void)
{
	this->player_ = this->owner()->scene()->System<PlayerSystem>()->player();
	this->renderer_ = this->owner()->Component<Renderer>();
	
	this->renderer_->animation()->SetAnimation("default", 9);
	this->renderer_->animation()->SetIntercept(this->renderer_->Find("xxx"), this->transform_);
	*this->transform_ = *this->renderer_->model_list(this->renderer_->Find("xxx"))->transform();
}

void StageEvent::Update(void)
{
	auto position = this->transform_->position();
	position.x += 0.01f;
	this->transform_->set_position(position);
	auto rotation = this->transform_->rotation();
	rotation.y += 0.6f;
	this->transform_->set_rotation(rotation);
}

Transform * const StageEvent::transform(void) const
{
	return this->transform_;
}
