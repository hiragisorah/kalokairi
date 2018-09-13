#pragma once

#include "..\frame-work\engine.h"
#include "transform.h"

class EnemySystem : public Seed::System
{
public:
	EnemySystem(void);

public:
	void Initialize(void) override;
	void Update(void) override;

private:
	unsigned int frame_cnt_;
	Transform * core_transform_;
};