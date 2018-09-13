#include "pistol.h"

void Pistol::Initialize(void)
{
	this->AddComponent<Renderer>("pistol.hmodel", "pistol.hanim");
	this->AddComponent<PistolMovement>();

	this->renderer_ = this->Component<Renderer>();
	this->movement_ = this->Component<PistolMovement>();
}

Renderer * const Pistol::renderer(void)
{
	return this->renderer_;
}

Transform * const Pistol::transform(void) const
{
	return this->movement_->transform();
}

void Pistol::Shot(void)
{
	this->movement_->Shot();
}

void Pistol::Disappear(void)
{
	this->movement_->Disappear();
}
