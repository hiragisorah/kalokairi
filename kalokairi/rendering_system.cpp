#include "rendering_system.h"
#include "..\frame-work\scene.h"
#include "..\frame-work\engine.h"

void RenderingSystem::Initialize(void)
{
	auto graphics = this->owner()->engine()->graphics();

	this->view_ = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 6, -6, 0.f), DirectX::XMVectorZero(), DirectX::XMVectorSet(0, 1, 0, 0));
	this->projection_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, static_cast<float>(graphics->width()) / static_cast<float>(graphics->height()), 0.3f, 1000.f);
	this->eye_ = DirectX::Vector3(0, 6, -6);
	this->dir_light_ = DirectX::Vector3(0, -10, 5);

	this->backbuffer_ = graphics->CreateBackBuffer();
	
	this->col_map_ = graphics->CreateColorMap(graphics->width(), graphics->height());
	this->pos_map_ = graphics->CreatePositionMap(graphics->width(), graphics->height());
	this->nor_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	this->dep_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	
	this->dsv_ = graphics->CreateDepthStencil(graphics->width(), graphics->height());
	this->vp_ = graphics->CreateViewPort(graphics->width(), graphics->height());

	this->shader_backbuffer_ = graphics->CreateShader("../backbuffer3d.hlsl");
	this->shader_deffered_ = graphics->CreateShader("../deffered3d.hlsl");

	graphics->SetViewPort(this->vp_);
}

void RenderingSystem::Begin(Seed::Graphics & graphics)
{
	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, { this->dsv_ });
	graphics.SetTarget({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, this->dsv_);

	graphics.SetView(this->view_);
	graphics.SetProjection(this->projection_);
	graphics.SetEye(this->eye_);
	graphics.SetDirectionLight(this->dir_light_);
	
	graphics.UpdateMainConstantBuffer();

	graphics.SetShader(this->shader_deffered_);
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

	graphics.SetShader(this->shader_backbuffer_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ });

	graphics.Run();
}

void RenderingSystem::AddModel(HierarchyModel * const model)
{
	this->model_list_.emplace_back(model);
}

void RenderingSystem::Rendering(Seed::Graphics & graphics, HierarchyModel * const model)
{
	graphics.SetWorld(model->transform()->FinalMatrix());

	graphics.UpdateModelConstantBuffer();

	graphics.Draw(model->primitive_id());
}
