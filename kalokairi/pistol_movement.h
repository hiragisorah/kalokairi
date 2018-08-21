#pragma once

#include "..\frame-work\engine.h"
#include "renderer.h"

class PistolMovement : public Seed::Component
{
public:
	PistolMovement(void);
	~PistolMovement(void);

public:
	void Initialize(void) override;
	void Update(void) override;

private:
	Renderer * renderer_;
	Transform * transform_;
	HierarchyModelList * model_list_;

public:
	Transform * const transform(void) const;

private:
	float fade_;
	bool disappear_;

public:
	void Disappear(void);

public:
	void Shot(void);
};