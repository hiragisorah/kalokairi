#include "collision.h"
#include "collision-system.h"

Collision::Collision(void)
{
}

Collider * const Collision::CreateCollider(Seed::Entity * const owner, const float & radius)
{
	return this->owner()->scene()->System<CollisionSystem>()->CreateCollider(owner, radius);
}