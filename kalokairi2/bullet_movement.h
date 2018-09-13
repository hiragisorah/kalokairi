#pragma once

#include "..\frame-work\engine.h"
#include "renderer.h"

class BulletMovement : public Seed::Component
{
public:
	BulletMovement(void);
	~BulletMovement(void);

public:
	void Initialize(void) override;
	void Update(void) override;

private:
	Renderer * renderer_;
	Transform * transform_;

private:
	int frame_cnt_;

public:
	Transform * const transform(void) const;
};