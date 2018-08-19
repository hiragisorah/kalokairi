#include "player.h"
#include "renderer.h"
#include "player_movement.h"

void Player::Initialize(void)
{
	this->AddComponent<Renderer>("stick_man_low2.hmodel", "human2.hanim");
	this->AddComponent<PlayerMovement>();
}