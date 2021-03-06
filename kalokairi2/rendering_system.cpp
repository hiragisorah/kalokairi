#include "rendering_system.h"
#include "..\frame-work\scene.h"
#include "..\frame-work\engine.h"

void RenderingSystem::Initialize(void)
{
	auto graphics = this->owner()->engine()->graphics();

	this->backbuffer_ = graphics->CreateBackBuffer();
	
	this->col_map_ = graphics->CreateColorMap(graphics->width(), graphics->height());
	this->pos_map_ = graphics->CreatePositionMap(graphics->width(), graphics->height());
	this->nor_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	this->dep_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	this->sha_map_ = graphics->CreateR32Map(graphics->width(), graphics->height());
	
	this->dsv_ = graphics->CreateDepthStencil(graphics->width(), graphics->height());
	this->vp_ = graphics->CreateViewPort(graphics->width(), graphics->height());

	this->shader_post_effects_ = graphics->CreateShader("../posteffects.hlsl");
	this->shader_backbuffer_ = graphics->CreateShader("../backbuffer3d.hlsl");
	this->shader_deffered_ = graphics->CreateShader("../deffered3d.hlsl");
	this->shader_shadow_ = graphics->CreateShader("../shadowmap.hlsl");
}

void RenderingSystem::Begin(Seed::Graphics & graphics)
{
	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_, this->sha_map_ }, { this->dsv_ });
	
	graphics.SetViewPort(this->vp_);
}

void RenderingSystem::Render(Seed::Graphics & graphics)
{
	graphics.SetTarget({ this->sha_map_ }, this->dsv_);
	
	graphics.SetShader(this->shader_shadow_);

	graphics.UpdateMainConstantBuffer();

	for (auto & model : this->model_list_)
		this->Rendering(graphics, model);

	graphics.ClearTarget({}, { this->dsv_ });

	graphics.SetTarget({ this->col_map_, this->pos_map_, this->nor_map_ }, this->dsv_);

	graphics.SetShader(this->shader_deffered_);

	for (auto & model : this->model_list_)
		this->Rendering(graphics, model);

	this->model_list_.clear();
}

void RenderingSystem::End(Seed::Graphics & graphics)
{
	graphics.ClearTarget({}, { this->dsv_ });

	graphics.SetTarget({ this->dep_map_ }, this->dsv_);

	graphics.SetShader(this->shader_backbuffer_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->sha_map_ });

	graphics.ClearTarget({ }, { this->dsv_ });

	graphics.SetTarget({ this->backbuffer_ }, this->dsv_);

	graphics.SetShader(this->shader_post_effects_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ });

	graphics.Run();
}

void RenderingSystem::AddModel(HierarchyModel * const model)
{
	if(model->primitive_id() != -1)
		this->model_list_.emplace_back(model);
}

void RenderingSystem::Rendering(Seed::Graphics & graphics, HierarchyModel * const model)
{
	graphics.SetWorld(model->transform()->FinalMatrix());
	graphics.SetDiffuse(model->diffuse());

	graphics.UpdateModelConstantBuffer();

	graphics.Draw(model->primitive_id());
}
