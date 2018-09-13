#include "collision-system.h"
#include <algorithm>

CollisionSystem::CollisionSystem(void)
{
}

CollisionSystem::~CollisionSystem(void)
{
	for (auto & collider : this->colliders_)
		delete collider;
}

Collider * const CollisionSystem::CreateCollider(Seed::Entity * const owner, const float & radius)
{
	auto collider = new Collider;
	collider->set_radius(radius);
	collider->set_owner(owner);
	this->colliders_.emplace_back(collider);
	return collider;
}

void CollisionSystem::Update(void)
{
	auto copy(this->colliders_);
	auto copy2(this->colliders_);

	int i = 0;
	std::for_each(copy.begin(), copy.end(), [&](Collider * collider)
	{
		if (!collider->is_alive())
		{
			delete this->colliders_[i];
			this->colliders_.erase(this->colliders_.begin() + i);
		}
		else
		{
			int n = 0;
			std::for_each(copy2.begin(), copy2.end(), [&](Collider * target)
			{
				if (i != n)
				{
					auto distance = DirectX::Vector3::Distance(collider->position(), target->position());
					if (distance < collider->radius() + target->radius())
					{
						if(collider->hit_call_back())	
							collider->hit_call_back()(collider, target);
						if(target->hit_call_back())
							target->hit_call_back()(target, collider);
					}
				}
				n++;
			});
			++i;
		}
	});
}
