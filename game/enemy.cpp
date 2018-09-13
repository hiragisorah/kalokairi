#include "enemy.h"
#include "enemy_event.h"
#include "collision.h"

void Enemy::Initialize(void)
{
	this->AddComponent<Renderer>("enemy.hmodel", "enemy.hanim");

	this->AddComponent<Collision>();
	this->AddComponent<EnemyEvent>();

	this->renderer_ = this->Component<Renderer>();
}
