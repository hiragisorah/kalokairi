#pragma once

#include "..\frame-work\engine.h"
#include "transform.h"
#include "hierarchy-animation.h"
#include "renderer.h"

class PlayerMovement : public Seed::Component
{
public:
	PlayerMovement(void);

public:
	void Initialize(void) override;
	void Update(void) override;
	void Always(void) override;
	void Finalize(void) override;

private:
	Transform * transform_;
	Animation * root_animation_;
	Renderer * renderer_;

};