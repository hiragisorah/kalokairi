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
	
	this->dsv_ = graphics->CreateDepthStencil(graphics->width(), graphics->height());
	this->vp_ = graphics->CreateViewPort(graphics->width(), graphics->height());

	this->shader_ = graphics->CreateShader("../backbuffer3d.hlsl");

	graphics->SetViewPort(this->vp_);
}

void RenderingSystem::Begin(Seed::Graphics & graphics)
{
	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_ }, { this->dsv_ });
	graphics.SetTarget({ this->col_map_, this->pos_map_, this->nor_map_ }, this->dsv_);
}

void RenderingSystem::Render(Seed::Graphics & graphics)
{
	for (auto & model : this->model_list_)
		this->Rendering(graphics, model);

	this->model_list_.clear();
}

void RenderingSystem::End(Seed::Graphics & graphics)
{
	graphics.SetTarget({ this->backbuffer_ }, this->dsv_);

	graphics.SetShader(this->shader_, nullptr);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_ });

	graphics.Run();
}

void RenderingSystem::AddModel(HierarchyModel * const model)
{
	this->model_list_.emplace_back(model);
}

void RenderingSystem::Rendering(Seed::Graphics & graphics, HierarchyModel * const model)
{
	graphics.SetShader(model->shader_id(), model->constant_buffer());
	graphics.Draw(model->primitive_id());
}
