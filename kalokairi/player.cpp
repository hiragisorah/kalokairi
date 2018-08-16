#include "player.h"
#include "renderer.h"

void Player::Initialize(void)
{
	this->AddComponent<Renderer>();
}
