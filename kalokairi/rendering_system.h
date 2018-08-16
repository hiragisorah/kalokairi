#pragma once

#include "..\frame-work\system.h"
#include "hierarchy-model.h"

class RenderingSystem : public Seed::System
{
public:
	void Initialize(void) override;
	void Begin(Seed::Graphics & graphics) override;
	void Render(Seed::Graphics & graphics) override;
	void End(Seed::Graphics & graphics) override;

private:
	std::vector<HierarchyModel*> model_list_;

public:
	void AddModel(HierarchyModel * const model);

private:
	void Rendering(Seed::Graphics & graphics, HierarchyModel * const model);

private:
	unsigned int rtv_;
	unsigned int dsv_;
	unsigned int vp_;
};