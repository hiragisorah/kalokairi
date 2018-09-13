#include "title-rendering-system.h"
#include "..\frame-work\scene.h"
#include "..\frame-work\engine.h"
#include "result-scene.h"
#include "..\input\input.h"

void TitleRenderingSystem::Initialize(void)
{
	auto graphics = this->owner()->engine()->graphics();

	graphics->SetScreenColor({ 1,1,1,1 });

	this->backbuffer_ = graphics->CreateBackBuffer();

	this->col_map_ = graphics->CreateColorMap(graphics->width(), graphics->height());
	this->pos_map_ = graphics->CreatePositionMap(graphics->width(), graphics->height());
	this->nor_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	this->dep_map_ = graphics->CreateNormalMap(graphics->width(), graphics->height());
	this->sha_map_ = graphics->CreateR32Map(graphics->width(), graphics->height());

	this->dsv_ = graphics->CreateDepthStencil(graphics->width(), graphics->height());
	this->vp_ = graphics->CreateViewPort(graphics->width(), graphics->height());

	this->shader_post_effects_ = graphics->CreateShader("data/hlsl/posteffects.hlsl");
	this->shader_backbuffer_ = graphics->CreateShader("data/hlsl/backbuffer3d.hlsl");
	this->shader_2d_ = graphics->CreateShader("data/hlsl/backbuffer2d.hlsl");
	this->shader_deffered_ = graphics->CreateShader("data/hlsl/deffered3d.hlsl");
	this->shader_shadow_ = graphics->CreateShader("data/hlsl/shadowmap.hlsl");

	this->title_tex_ = graphics->CreateTexture("data/texture/title.png");
	this->press_tex_ = graphics->CreateTexture("data/texture/press-key.png");

	this->end_cnt = -1;
	this->start_cnt = 90;
}

void TitleRenderingSystem::Always(void)
{

}

void TitleRenderingSystem::Begin(Seed::Graphics & graphics)
{
	if (start_cnt > 0)
	{
		graphics.SetScreenColor(DirectX::Vector4(1.f - start_cnt / 90.f, 1.f - start_cnt / 90.f, 1.f - start_cnt / 90.f, 1.f - start_cnt / 90.f));
		start_cnt--;
	}

	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_, this->sha_map_ }, { this->dsv_ });

	graphics.SetViewPort(this->vp_);
}

void TitleRenderingSystem::Render(Seed::Graphics & graphics)
{
	if (Seed::Input::Trigger(VK_SPACE))
	{
		end_cnt = 90;
		this->owner()->engine()->ChangeScene<ResultScene>();
	}

	if (end_cnt > 0)
	{
		graphics.SetScreenColor(DirectX::Vector4(end_cnt / 90.f, end_cnt / 90.f, end_cnt / 90.f, end_cnt / 90.f));
		end_cnt--;
	}
	if(end_cnt == 0)
	{
		this->owner()->Destroy();
	}
}

void TitleRenderingSystem::End(Seed::Graphics & graphics)
{
	graphics.SetBlend(false);

	static int frame_cnt = 0;

	graphics.ClearTarget({}, { this->dsv_ });

	graphics.SetTarget({ this->dep_map_ }, this->dsv_);

	graphics.SetShader(this->shader_backbuffer_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->sha_map_ });

	graphics.SetTarget({ this->dep_map_ }, -1);

	//
	graphics.SetBlend(true);

	graphics.SetShader(this->shader_2d_);

	auto size = graphics.GetTextureSize(this->title_tex_);
	graphics.SetDiffuse({ 1,1,1,1 });
	auto mtx = DirectX::Matrix::CreateScale(size.x / graphics.width(), size.y / graphics.height(), 1);
	graphics.SetWorld(mtx);
	graphics.UpdateModelConstantBuffer();
	graphics.DrawTexture(this->title_tex_);

	size = graphics.GetTextureSize(this->press_tex_);
	graphics.SetDiffuse({ 1,1,1, static_cast<float>(frame_cnt % 60) / 60.f });
	mtx = DirectX::Matrix::CreateScale(size.x / graphics.width(), size.y / graphics.height(), 1);
	mtx *= DirectX::Matrix::CreateTranslation(DirectX::Vector3(0, -0.5f, 0));
	graphics.SetWorld(mtx);
	graphics.UpdateModelConstantBuffer();
	graphics.DrawTexture(this->press_tex_);

	graphics.SetBlend(false);
	//

	graphics.ClearTarget({}, { this->dsv_ });

	graphics.SetTarget({ this->backbuffer_ }, this->dsv_);

	graphics.SetShader(this->shader_post_effects_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ });

	graphics.Run();

	frame_cnt++;
}

void TitleRenderingSystem::AddModel(HierarchyModel * const model)
{
	if (model->primitive_id() != -1)
		this->model_list_.emplace_back(model);
}

void TitleRenderingSystem::Rendering(Seed::Graphics & graphics, HierarchyModel * const model)
{
	graphics.SetWorld(model->transform()->FinalMatrix());
	graphics.SetDiffuse(model->diffuse());

	graphics.UpdateModelConstantBuffer();

	graphics.Draw(model->primitive_id());
}
