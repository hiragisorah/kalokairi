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
	unsigned int shader_backbuffer_;
	unsigned int shader_deffered_;

	unsigned int backbuffer_;

	unsigned int col_map_;
	unsigned int pos_map_;
	unsigned int nor_map_;
	unsigned int dep_map_;

	unsigned int dsv_;
	unsigned int vp_;

private:
	DirectX::XMMATRIX view_;
	DirectX::XMMATRIX projection_;
	DirectX::Vector3 eye_;
	DirectX::Vector3 dir_light_;
};