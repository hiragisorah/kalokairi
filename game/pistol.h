#pragma once

#include "..\frame-work\engine.h"

#include "renderer.h"
#include "pistol_movement.h"

class Pistol : public Seed::Entity
{
public:
	void Initialize(void) override;

private:
	Renderer * renderer_;
	PistolMovement * movement_;

public:
	Renderer * const renderer(void);

public:
	Transform * const transform(void) const;

public:
	void Shot(void);
	void Disappear(void);
};