#include "renderer.h"
#include "..\frame-work\engine.h"
#include "rendering_system.h"

void Renderer::Initialize(void)
{
	auto graphics = this->owner()->scene()->engine()->graphics();
	
	auto & model = this->model_list_[0];
	
	this->constant_buffer_.world_ = DirectX::XMMatrixIdentity();
	this->constant_buffer_.view_ = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 5, -5, 0.f), DirectX::XMVectorZero(), DirectX::XMVectorSet(0, 1, 0, 0));
	this->constant_buffer_.projection_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, static_cast<float>(graphics->width()) / static_cast<float>(graphics->height()), 0.3f, 1000.f);
	this->constant_buffer_.eye_ = { 0, 5, -5 };

	model.set_primitive_id(graphics->CreateSphere());
	model.set_shader_id(graphics->CreateShader("../default3d.hlsl"));
	model.set_constant_buffer(&this->constant_buffer_);
}

void Renderer::Always(void)
{
	auto rs = this->owner()->scene()->System<RenderingSystem>();

	for (auto & model : this->model_list_)
		rs->AddModel(&model.second);
}

void Renderer::Finalize(void)
{
	
}
