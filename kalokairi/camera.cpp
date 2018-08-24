#include "camera.h"
#include <algorithm>

Camera::Camera(void)
	: eye_(0,5,-5)
	, at_(0,0,0)
	, up_(0,1,0)
	, fov_(DirectX::XM_PIDIV4)
	, aspect_(1280.f / 720.f)
	, near_(0.5f)
	, far_(20.f)
	, target_(nullptr)
{
}

void Camera::Initialize(void)
{
	auto graphics = this->owner()->engine()->graphics();
	this->aspect_ = static_cast<float>(graphics->width()) / static_cast<float>(graphics->height());
}

#undef max
#undef min

void Camera::Update(void)
{
	if (this->target_)
	{
		auto position = this->target_->FinalMatrix().Translation();
		this->at_ = DirectX::Vector3::Lerp(this->eye_, position, 0.1f);
		//this->eye_ = DirectX::Vector3::Lerp(this->eye_, position + back * 5.f + DirectX::Vector3(0, 1.f, 0), 0.05f);
		this->eye_ = DirectX::Vector3::Lerp(this->eye_, position - DirectX::Vector3(0, -2.f, 5.f), 0.05f);
		this->eye_ += 0.20f * DirectX::Vector3::Down + DirectX::Vector3::Up * DirectX::Vector3::Distance(this->eye_, position) * 0.05f;
	}
}

void Camera::Always(void)
{
	this->dir_light_ = DirectX::Vector3(0, 8, -8);
	this->dir_light_.x += this->eye_.x;
}

void Camera::Finalize(void)
{
}

void Camera::Begin(Seed::Graphics & graphics)
{
	graphics.SetView(this->View());
	graphics.SetProjection(this->Projection());
	graphics.SetEye(this->eye_);
	graphics.SetDirectionLight(this->dir_light_);
}

void Camera::End(Seed::Graphics & graphics)
{
}

const DirectX::Vector3 & Camera::eye(void)
{
	return this->eye_;
}

const DirectX::Vector3 & Camera::at(void)
{
	return this->at_;
}

const DirectX::Vector3 & Camera::up(void)
{
	return this->up_;
}

void Camera::set_eye(const DirectX::Vector3 & eye)
{
	this->eye_ = eye;
}

void Camera::set_at(const DirectX::Vector3 & at)
{
	this->at_ = at;
}

void Camera::set_up(const DirectX::Vector3 & up)
{
	this->up_ = up;
}

void Camera::set_fov(const float & fov)
{
	this->fov_ = fov;
}

void Camera::set_aspect(const float & aspect)
{
	this->aspect_ = aspect;
}

void Camera::set_near(const float & near)
{
	this->near_ = near;
}

void Camera::set_far(const float & far)
{
	this->far_ = far;
}

DirectX::Matrix Camera::View(void)
{
	return DirectX::Matrix::CreateLookAt(this->eye_, this->at_, this->up_);
}

DirectX::Matrix Camera::Projection(void)
{
	return DirectX::Matrix::CreatePerspectiveFieldOfView(this->fov_, this->aspect_, this->near_, this->far_);
}

void Camera::set_target(Transform * const target)
{
	this->target_ = target;
}
