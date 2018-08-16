#include "component.h"

Seed::Component::Component(void)
	: owner_(nullptr)
{
}

Seed::Component::~Component(void)
{
}

void Seed::Component::set_owner(Entity * const owner)
{
	this->owner_ = owner;
}

Seed::Entity * const Seed::Component::owner(void)
{
	return this->owner_;
}
