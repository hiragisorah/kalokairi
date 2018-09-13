#pragma once

#include "..\frame-work\engine.h"
#include "renderer.h"

class Stage : public Seed::Entity
{
public:
	void Initialize(void) override;

private:
	Renderer * renderer_;
};