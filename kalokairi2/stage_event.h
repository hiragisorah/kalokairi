#pragma once

#include "..\frame-work\engine.h"
#include "player_system.h"
#include "renderer.h"

class StageEvent final : public Seed::Component
{
public:
	StageEvent(void);
	~StageEvent(void);

public:
	void Initialize(void) override;
	void Update(void) override;

private:
	Player * player_;
	Renderer * renderer_;
	Transform * transform_;

public:
	Transform * const transform(void) const;
};