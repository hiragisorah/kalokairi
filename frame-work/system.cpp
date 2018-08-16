#include "system.h"

Seed::System::System(void)
	: owner_(nullptr)
{
}

Seed::System::~System(void)
{
}

void Seed::System::set_owner(Scene * const owner)
{
	this->owner_ = owner;
}

Seed::Scene * const Seed::System::owner(void) const
{
	return this->owner_;
}
