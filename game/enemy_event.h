#pragma once

#include "..\frame-work\engine.h"
#include "player_system.h"
#include "renderer.h"
#include "collision.h"

class EnemyEvent final : public Seed::Component
{
public:
	EnemyEvent(void);
	~EnemyEvent(void);

public:
	void Initialize(void) override;
	void Finalize(void) override;
	void Update(void) override;

private:
	Player * player_;
	Renderer * renderer_;
	Transform * transform_;
	HierarchyModel * ball_model_;
	Collider * collider_;
	Transform * core_transform_;
	float hit_effect_;
	float end_effect_;
	float start_effect_;

public:
	Transform * const transform(void) const;

private:
	static void OnHit(Collider * collider, Collider * target);
};