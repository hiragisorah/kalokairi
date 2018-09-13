#pragma once

#include "..\frame-work\engine.h"

#include "renderer.h"
#include "bullet_movement.h"
#include "collision.h"

class Bullet : public Seed::Entity
{
public:
	void Initialize(void) override;

private:
	Renderer * renderer_;
	BulletMovement * movement_;

public:
	Renderer * const renderer(void);

public:
	Transform * const transform(void) const;

public:
};