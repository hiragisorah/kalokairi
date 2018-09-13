#pragma once

#include "..\frame-work\engine.h"
#include "transform.h"
#include "hierarchy-animation.h"
#include "renderer.h"
#include "pistol.h"
#include "camera.h"

class PlayerMovement final : public Seed::Component
{
public:
	PlayerMovement(void);
	~PlayerMovement(void);

public:
	void Initialize(void) override;
	void Update(void) override;
	void Always(void) override;
	void Finalize(void) override;

private:
	Transform * transform_;
	Renderer * renderer_;
	Pistol * pistol_;
	Transform * r_arm1_;
	Transform * r_hand_;
	HierarchyModelList * model_list_;

private:
	int r_arm1_id_;
	float fade_;
	Camera * camera_;

public:
	Transform * const transform(void);
	Pistol * const pistol(void);
};