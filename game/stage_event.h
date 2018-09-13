#pragma once

#include "..\frame-work\engine.h"
#include "player_system.h"
#include "renderer.h"
#include "collision.h"

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
	HierarchyModel * ball_model_;
	Collider * collider_;

	float hit_effect_;
	
public:
	Transform * const transform(void) const;
	const bool is_end(void) const;

private:
	static void OnHit(Collider * collider, Collider * target);
};