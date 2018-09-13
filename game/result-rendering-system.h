#pragma once

#include "..\frame-work\system.h"
#include "hierarchy-model.h"

class ResultRenderingSystem : public Seed::System
{
public:
	void Initialize(void) override;
	void Always(void) override;
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
	unsigned int shader_post_effects_;
	unsigned int shader_backbuffer_;
	unsigned int shader_deffered_;
	unsigned int shader_shadow_;
	unsigned int shader_2d_;

	unsigned int backbuffer_;

	unsigned int col_map_;
	unsigned int pos_map_;
	unsigned int nor_map_;
	unsigned int dep_map_;
	unsigned int sha_map_;

	unsigned int dsv_;
	unsigned int vp_;

private:
	unsigned int title_tex_;
	unsigned int press_tex_;
	int end_cnt;
	int start_cnt;

private:
	DirectX::Vector3 dir_light_;
};