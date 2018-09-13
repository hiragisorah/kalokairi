#include "stage_event.h"
#include "enemy.h"

StageEvent::StageEvent(void)
	: transform_(new Transform)
	, collider_(nullptr)
	, hit_effect_(0)
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
	auto board_id = this->renderer_->Find("xxx");
	auto model = this->renderer_->model_list(board_id);
	*this->transform_ = *model->transform();
	model->set_diffuse({ .5f,1.f,.5f,1 });
	this->renderer_->animation()->SetIntercept(board_id, this->transform_);
	this->ball_model_ = this->renderer_->model_list(this->renderer_->Find("ball"));
	this->collider_ = this->owner()->Component<Collision>()->CreateCollider(this->owner(), .6f);
	this->collider_->set_hit_call_back(this->OnHit);
	this->collider_->set_type(1);
}

void StageEvent::Update(void)
{
	this->collider_->set_position(this->ball_model_->transform()->FinalPosition());

	auto position = this->transform_->position();
	position.x += 0.01f + this->hit_effect_ * 0.012f;
	this->transform_->set_position(position);
	auto rotation = this->transform_->rotation();
	rotation.y += 0.6f + this->hit_effect_ * 1.2f;
	this->transform_->set_rotation(rotation);

	this->ball_model_->set_diffuse(DirectX::Vector4(this->hit_effect_ * .5f, .5f + this->hit_effect_ * .5f, this->hit_effect_ * .5f, 1));
}

Transform * const StageEvent::transform(void) const
{
	return this->transform_;
}

const bool StageEvent::is_end(void) const
{
	return this->hit_effect_ <= -.5f;
}

void StageEvent::OnHit(Collider * collider, Collider * target)
{
	if (target->type() == 0)
	{
		auto self = collider->owner()->Component<StageEvent>();

		if (self->hit_effect_ < 1.f)
			self->hit_effect_ += 0.01f;
	}
	else if (target->type() == 2)
	{
		auto self = collider->owner()->Component<StageEvent>();

		self->hit_effect_ -= 0.002f;
	}
}
