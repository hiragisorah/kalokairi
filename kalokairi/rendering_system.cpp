#include "rendering_system.h"
#include "..\frame-work\scene.h"
#include "..\frame-work\engine.h"

void RenderingSystem::Initialize(void)
{
	auto graphics = this->owner()->engine()->graphics();
	this->rtv_ = graphics->CreateBackBuffer();
	this->dsv_ = graphics->CreateDepthStencil(graphics->width(), graphics->height());
	this->vp_ = graphics->CreateViewPort(graphics->width(), graphics->height());

	graphics->ClearTarget({ this->rtv_ }, { this->dsv_ });
	graphics->SetTarget({ this->rtv_ }, this->dsv_);
	graphics->SetViewPort(this->vp_);
}

void RenderingSystem::Begin(Seed::Graphics & graphics)
{
	graphics.ClearTarget({ this->rtv_ }, { this->dsv_ });
}

void RenderingSystem::Render(Seed::Graphics & graphics)
{
	for (auto & model : this->model_list_)
		this->Rendering(graphics, model);

	this->model_list_.clear();
}

void RenderingSystem::End(Seed::Graphics & graphics)
{
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
