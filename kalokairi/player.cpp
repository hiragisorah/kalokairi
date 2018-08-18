#include "player.h"
#include "renderer.h"
#include "player_movement.h"

void Player::Initialize(void)
{
	this->AddComponent<Renderer>("stick_man_low.hmodel", "human.hanim");
	this->AddComponent<PlayerMovement>();
}