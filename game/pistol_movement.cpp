#include "pistol_movement.h"
#include "bullet.h"

PistolMovement::PistolMovement(void)
	: transform_(new Transform)
	, model_list_(nullptr)
	, fade_(0.f)
	, disappear_(false)
{
}

PistolMovement::~PistolMovement(void)
{
	delete this->transform_;
}

void PistolMovement::Initialize(void)
{
	this->renderer_ = this->owner()->Component<Renderer>();
	this->renderer_->animation()->SetIntercept(0, this->transform_);

	this->model_list_ = this->renderer_->model_list();

	for (auto & model : *this->model_list_)
	{
		model.second.set_diffuse(DirectX::Vector4(.2f, .2f, 1.f, 0.f));
	}
}

void PistolMovement::Update(void)
{
	if (!this->disappear_ && this->fade_ <= 1.f)
	{
		for (auto & model : *this->model_list_)
		{
			model.second.set_diffuse(DirectX::Vector4(.2f, .2f, 1.f, this->fade_));
		}
		this->fade_ += 0.03f;
	}

	if (this->disappear_)
	{
		if (this->fade_ >= 0.f)
		{
			for (auto & model : *this->model_list_)
			{
				model.second.set_diffuse(DirectX::Vector4(.2f, .2f, 1.f, this->fade_));
			}
			this->fade_ -= 0.03f;
		}
		else
		{
			this->owner()->Destroy();
		}
	}
}

Transform * const PistolMovement::transform(void) const
{
	return this->transform_;
}

void PistolMovement::Disappear(void)
{
	this->disappear_ = true;
}

void PistolMovement::Shot(void)
{
	auto bullet = this->owner()->scene()->CreateEntity<Bullet>();
	auto movement = bullet->Component<BulletMovement>();
	auto self_position = this->transform_->FinalPosition();
	auto self_rotation = this->transform_->FinalRotation();
	movement->transform()->set_position(self_position - self_position.Forward * 0.1f + self_position.Up * 0.01f);
	movement->transform()->set_rotation(self_rotation);
}
