#pragma once

#include "..\frame-work\engine.h"
#include "collider.h"

class Collision : public Seed::Component
{
public:
	Collision(void);

public:
	Collider * const CreateCollider(Seed::Entity * const owner, const float & radius);
};