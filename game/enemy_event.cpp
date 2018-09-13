#include "enemy_event.h"
#include "stage_system.h"
#include "stage_event.h"

EnemyEvent::EnemyEvent(void)
	: transform_(new Transform)
	, collider_(nullptr)
	, core_transform_(nullptr)
	, start_effect_(0)
	, hit_effect_(0)
	, end_effect_(1)
{
}

EnemyEvent::~EnemyEvent(void)
{
	delete this->transform_;
}

void EnemyEvent::Initialize(void)
{
	this->player_ = this->owner()->scene()->System<PlayerSystem>()->player();
	this->renderer_ = this->owner()->Component<Renderer>();

	this->renderer_->animation()->SetAnimation("default", 9);
	auto root_id = this->renderer_->Find("root");
	*this->transform_ = *this->renderer_->model_list(root_id)->transform();
	this->renderer_->animation()->SetIntercept(root_id, this->transform_);
	this->ball_model_ = this->renderer_->model_list(this->renderer_->Find("ball"));
	this->collider_ = this->owner()->Component<Collision>()->CreateCollider(this->owner(), .6f);
	this->collider_->set_hit_call_back(this->OnHit);
	this->collider_->set_type(2);
	this->core_transform_ = this->owner()->scene()->System<StageSystem>()->stage()->Component<StageEvent>()->transform();
}

void EnemyEvent::Finalize(void)
{
	this->collider_->Destroy();
}

void EnemyEvent::Update(void)
{
	auto position = this->transform_->position();
	auto target_position = this->core_transform_->FinalPosition();
	auto vec = target_position - position;
	//if (vec.Length() < 10.f)
	{
		vec.Normalize();
		this->transform()->set_position(position + vec * 0.025f);
	}

	if (start_effect_ < 1.f)
		this->start_effect_ += 0.05f;

		this->collider_->set_position(this->ball_model_->transform()->FinalPosition());

	this->ball_model_->set_diffuse(DirectX::Vector4(.3f + this->hit_effect_ * .7f, this->hit_effect_ * .9f, this->hit_effect_ * .9f, this->end_effect_ * this->start_effect_));

	if (this->hit_effect_ > 1.f)
		this->end_effect_ -= 0.05f;

	if (this->end_effect_ < 0)
		this->owner()->Destroy();
}

Transform * const EnemyEvent::transform(void) const
{
	return this->transform_;
}

void EnemyEvent::OnHit(Collider * collider, Collider * target)
{
	if (target->type() == 0)
	{
		auto self = collider->owner()->Component<EnemyEvent>();

		if(self->hit_effect_ < 1.f)
			self->hit_effect_ += 0.15f;
		//collider->owner()->Destroy();
		
	}
}
