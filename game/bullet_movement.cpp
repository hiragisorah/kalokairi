#include "bullet_movement.h"
#include "collision.h"

BulletMovement::BulletMovement(void)
	: transform_(new Transform)
	, frame_cnt_(0)
	, collider_(nullptr)
{
}

BulletMovement::~BulletMovement(void)
{
	delete this->transform_;
}

void BulletMovement::Initialize(void)
{
	this->renderer_ = this->owner()->Component<Renderer>();
	this->renderer_->animation()->SetIntercept(0, this->transform_);
	this->transform_->set_scale(DirectX::Vector3(0.4f, 0.4f, 0.4f));
	this->collider_ = this->owner()->Component<Collision>()->CreateCollider(this->owner(), 0.1f);
	this->collider_->set_hit_call_back(this->OnHit);
	this->collider_->set_type(0);
}

void BulletMovement::Update(void)
{
	this->transform()->MoveRight(0.5f);

	this->collider_->set_position(this->transform_->FinalPosition());

	if (this->frame_cnt_++ > 120)
	{
		this->owner()->Destroy();
	}
}

void BulletMovement::Finalize(void)
{
	this->collider_->Destroy();
}

Transform * const BulletMovement::transform(void) const
{
	return this->transform_;
}

void BulletMovement::OnHit(Collider * collider, Collider * target)
{
	if (target->type() == 2 || target->type() == 1)
	{
		collider->owner()->Destroy();
	}
}
