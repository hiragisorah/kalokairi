#include "player.h"
#include "renderer.h"
#include "player_movement.h"

void Player::Initialize(void)
{
	this->AddComponent<Renderer>("stick_man_low2.hmodel", "human7.hanim");
	this->AddComponent<PlayerMovement>();
	this->transform_ = this->Component<PlayerMovement>()->transform();
}

Transform * const Player::transform(void) const
{
	return this->transform_;
}
