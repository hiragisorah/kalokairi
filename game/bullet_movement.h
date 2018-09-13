#pragma once

#include "..\frame-work\engine.h"
#include "renderer.h"
#include "collider.h"

class BulletMovement : public Seed::Component
{
public:
	BulletMovement(void);
	~BulletMovement(void);

public:
	void Initialize(void) override;
	void Update(void) override;
	void Finalize(void) override;

private:
	Renderer * renderer_;
	Transform * transform_;
	Collider * collider_;

private:
	int frame_cnt_;

public:
	Transform * const transform(void) const;
	
private:
	static void OnHit(Collider * collider, Collider * target);
};