#include "player_system.h"

PlayerSystem::PlayerSystem(void)
{
	
}

void PlayerSystem::Initialize(void)
{
	this->player_ = this->owner()->CreateEntity<Player>();
}

Player * const PlayerSystem::player(void)
{
	return this->player_;
}
