#include "bullet_movement.h"

BulletMovement::BulletMovement(void)
	: transform_(new Transform)
	, frame_cnt_(0)
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
}

void BulletMovement::Update(void)
{
	this->transform()->MoveRight(0.5f);

	if (this->frame_cnt_++ > 120)
	{
		this->owner()->Destroy();
	}
}

Transform * const BulletMovement::transform(void) const
{
	return this->transform_;
}
