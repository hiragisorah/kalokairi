#include "renderer.h"
#include "..\frame-work\engine.h"
#include "rendering_system.h"
#include "kalokairi.h"

#include "..\QtGui\item.h"

Renderer::Renderer(void)
	: transform_(new Transform)
{
}

void Renderer::Initialize(void)
{
	auto graphics = this->owner()->scene()->engine()->graphics();
	
	this->ReadHierarchyFromFile("stick_man_low.hmodel");
	this->ReadHierarchyAnimationFromFile("human.hanim");

	auto shader_id = graphics->CreateShader("../default3d.hlsl");

	for (auto & model_map : this->model_list_)
	{
		auto & model = model_map.second;

		this->constant_buffer_[model_map.first].world_ = model.transform()->FinalMatrix();
		this->constant_buffer_[model_map.first].view_ = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 5, -5, 0.f), DirectX::XMVectorZero(), DirectX::XMVectorSet(0, 1, 0, 0));
		this->constant_buffer_[model_map.first].projection_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, static_cast<float>(graphics->width()) / static_cast<float>(graphics->height()), 0.3f, 1000.f);
		this->constant_buffer_[model_map.first].eye_ = { 0, 5, -5 };

		model.set_shader_id(shader_id);
		model.set_constant_buffer(&this->constant_buffer_[model_map.first]);
	}

	this->root_animation_.frames_.resize(1);

	this->animation_.SetAnimation("idle", 1);
	this->animation_.SetAnimation(&this->root_animation_, 0);

	this->animation_.set_model_list(&this->model_list_);
}

void Renderer::Update(void)
{
	auto & transform = this->root_animation_.frames_[0].transforms_[0];

	float move_side = static_cast<float>(Input::Press(Qt::Key_D)) - static_cast<float>(Input::Press(Qt::Key_A));
	
	float move_forward = static_cast<float>(Input::Press(Qt::Key_W)) - static_cast<float>(Input::Press(Qt::Key_S));

	float rot_side = static_cast<float>(Input::Press(Qt::Key_Q)) - static_cast<float>(Input::Press(Qt::Key_E));

	if (move_side || move_forward)
	{
		this->animation_.SetAnimation("walk", 1);
	}
	else
	{
		this->animation_.SetAnimation("idle", 1);
	}

	float move_speed = 0.005f;

	this->transform_->RotateY(rot_side);
	this->transform_->MoveSide(move_side * move_speed * 0.5f);
	this->transform_->MoveForward(move_forward * move_speed);

	transform.position_ = this->transform_->position();
	transform.rotation_ = this->transform_->rotation();
	transform.scale_ = this->transform_->scale();

	this->animation_.Update();

	for (auto & model_map : this->model_list_)
	{
		auto & model = model_map.second;
		this->constant_buffer_[model_map.first].world_ = model.transform()->FinalMatrix();
	}
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

void Renderer::ReadHierarchyFromFile(const std::string & file_name)
{
	auto graphics = this->owner()->scene()->engine()->graphics();

	this->model_list_.clear();

	std::unordered_map<int, ItemData> items;
	unsigned int cnt = 0;

	std::ifstream is(file_name, std::ios::binary);
	cereal::BinaryInputArchive in(is);
	in(cnt, items);

	for (auto & item : items)
	{
		auto & model = this->model_list_[item.second.self];
		auto & data = item.second;

		if (data.parent != -1)
			model.transform()->set_parent(this->model_list_[data.parent].transform());

		model.set_name(data.name);

		switch (data.primitive_type)
		{
		case 0:
			model.set_primitive_id(-1);
			break;
		case 1:
			model.set_primitive_id(graphics->CreatePlane(data.plane_div_x, data.plane_div_y, data.plane_size));
			break;
		case 2:
			model.set_primitive_id(graphics->CreateBox(data.box_size));
			break;
		case 3:
			model.set_primitive_id(graphics->CreateSphere(data.sphere_diameter, data.sphere_tessellation));
			break;
		case 4:
			model.set_primitive_id(graphics->CreateGeoSphere(data.geosphere_diameter, data.geosphere_tessellation));
			break;
		case 5:
			model.set_primitive_id(graphics->CreateCapsule(data.capsule_p1, data.capsule_p2, data.capsule_diameter, data.capsule_tessellation));
			break;
		}

		model.transform()->set_offset_position(data.offset_position);
		model.transform()->set_offset_rotation({ DirectX::XMConvertToDegrees(data.offset_rotation.x), DirectX::XMConvertToDegrees(data.offset_rotation.y), DirectX::XMConvertToDegrees(data.offset_rotation.z) });
		model.transform()->set_offset_scale(data.offset_scale);

		model.transform()->set_position(data.position);
		model.transform()->set_rotation({ DirectX::XMConvertToDegrees(data.rotation.x), DirectX::XMConvertToDegrees(data.rotation.y), DirectX::XMConvertToDegrees(data.rotation.z) });
		model.transform()->set_scale(data.scale);
	}
}

void Renderer::ReadHierarchyAnimationFromFile(const std::string & file_name)
{
	std::unordered_map<int, ItemData> main_data;
	std::unordered_map<int, AnimData> anim_data;
	unsigned int cnt = 0;

	std::ifstream is(file_name, std::ios::binary);
	cereal::BinaryInputArchive in(is);
	in(cnt, anim_data, main_data);

	is.close();

	for (auto & anim_map : anim_data)
	{
		auto & anim = anim_map.second;

		Animation animation;
		animation.frames_.resize(anim.frames.size());

		for (size_t n = 0; n < anim.frames.size(); ++n)
		{
			auto & fr = anim.frames[n];
			auto & sp = anim.speed[n];

			animation.frames_[n].speed_ = sp;
			for (auto & fr_map : fr)
			{
				auto & transform = animation.frames_[n].transforms_[fr_map.first];
				transform.position_ = fr_map.second.position;
				transform.rotation_ = { DirectX::XMConvertToDegrees(fr_map.second.rotation.x), DirectX::XMConvertToDegrees(fr_map.second.rotation.y), DirectX::XMConvertToDegrees(fr_map.second.rotation.z) };
				transform.scale_ = fr_map.second.scale;
			}
		}

		this->animation_.set_animation(anim.name, animation);
	}
}

const int Renderer::Find(const std::string & model_name)
{
	for (auto & model : this->model_list_)
	{
		if(model.second.name() == model_name)
			return model.first;
	}

	return -1;
}
