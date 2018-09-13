#include "bullet.h"

void Bullet::Initialize(void)
{
	this->AddComponent<Renderer>("bullet.hmodel", "bullet.hanim");
	this->AddComponent<BulletMovement>();

	this->renderer_ = this->Component<Renderer>();
	this->movement_ = this->Component<BulletMovement>();
}

Renderer * const Bullet::renderer(void)
{
	return this->renderer_;
}

Transform * const Bullet::transform(void) const
{
	return this->movement_->transform();
}