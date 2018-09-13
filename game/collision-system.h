#pragma once

#include <vector>

#include "..\frame-work\engine.h"

#include "collider.h"

class CollisionSystem final : public Seed::System
{
public:
	CollisionSystem(void);
	~CollisionSystem(void);

private:
	std::vector<Collider*> colliders_;

public:
	Collider * const CreateCollider(Seed::Entity * const owner, const float & radius);
	
public:
	void Update(void) override;
};