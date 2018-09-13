#include "transform.h"

Transform::Transform(
	DirectX::Vector3 position,
	DirectX::Vector3 rotation,
	DirectX::Vector3 scale,
	DirectX::Vector3 offset_position,
	DirectX::Vector3 offset_rotation,
	DirectX::Vector3 offset_scale)
	: parent_(nullptr)
	, position_(position)
	, rotation_(rotation)
	, scale_(scale)
	, offset_position_(offset_position)
	, offset_rotation_(offset_rotation)
	, offset_scale_(offset_scale)
{
}

Transform * const Transform::parent(void)
{
	return this->parent_;
}

void Transform::set_parent(Transform * const parent)
{
	this->parent_ = parent;
}

const DirectX::Vector3 & Transform::offset_position(void) const
{
	return this->offset_position_;
}

const DirectX::Vector3 & Transform::offset_rotation(void) const
{
	return this->offset_rotation_;
}

const DirectX::Vector3 & Transform::offset_scale(void) const
{
	return this->offset_scale_;
}

const DirectX::Vector3 & Transform::position(void) const
{
	return this->position_;
}

const DirectX::Vector3 & Transform::rotation(void) const
{
	return this->rotation_;
}

const DirectX::Vector3 & Transform::scale(void) const
{
	return this->scale_;
}

void Transform::set_offset_position(const DirectX::Vector3 & offset_position)
{
	this->offset_position_ = offset_position;
}

void Transform::set_offset_rotation(const DirectX::Vector3 & offset_rotation)
{
	this->offset_rotation_ = offset_rotation;
}

void Transform::set_offset_scale(const DirectX::Vector3 & offset_scale)
{
	this->offset_scale_ = offset_scale;
}

void Transform::set_position(const DirectX::Vector3 & position)
{
	this->position_ = position;
}

void Transform::set_position(const DirectX::Vector3 & position, const float & progress)
{
	this->position_ = this->position_ + (position - this->position_) * progress;
}

void Transform::set_fixed_rotation(const DirectX::Vector3 & rotation)
{
	DirectX::Quaternion q;
	DirectX::Vector3 t, s;
	auto m = this->parent_->FinalMatrix();
	m.Decompose(s, q, t);

	auto r = QuaternionToYawPitchRoll(q);

	r.y = 0;
	r.x = 0;

	this->rotation_ = rotation - r;
}

void Transform::set_rotation(const DirectX::Vector3 & rotation)
{
	this->rotation_ = rotation;
}

void Transform::set_rotation(const DirectX::Vector3 & rotation, const float & progress)
{
	DirectX::Quaternion a, b;

	a = DirectX::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(this->rotation_.y), DirectX::XMConvertToRadians(this->rotation_.x), DirectX::XMConvertToRadians(this->rotation_.z));
	b = DirectX::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(rotation.y), DirectX::XMConvertToRadians(rotation.x), DirectX::XMConvertToRadians(rotation.z));

	this->rotation_ = QuaternionToYawPitchRoll(DirectX::Quaternion::Slerp(a, b, progress));
}

void Transform::set_scale(const DirectX::Vector3 & scale)
{
	this->scale_ = scale;
}

void Transform::set_scale(const DirectX::Vector3 & scale, const float & progress)
{
	this->scale_ = this->scale_ + (scale - this->scale_) * progress;
}

void Transform::MoveForward(const float & speed)
{
	this->position_ += this->FinalMatrix().Forward() * speed;
}

void Transform::MoveLeft(const float & speed)
{
	this->position_ += this->FinalMatrix().Left() * speed;
}

void Transform::MoveRight(const float & speed)
{
	this->position_ += this->FinalMatrix().Left() * speed;
}

void Transform::RotateX(const float & speed)
{
	this->rotation_.x += speed;
}

void Transform::RotateY(const float & speed)
{
	this->rotation_.y += speed;
}

void Transform::RotateZ(const float & speed)
{
	this->rotation_.z += speed;
}

void Transform::Update(void)
{
}

DirectX::Matrix Transform::TransformMatrix(void)
{
	return DirectX::Matrix::CreateScale(this->scale_)
		* DirectX::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(this->rotation_.y), DirectX::XMConvertToRadians(this->rotation_.x), DirectX::XMConvertToRadians(this->rotation_.z))
		* DirectX::Matrix::CreateTranslation(this->position_);
}

DirectX::Matrix Transform::OffsetMatrix(void)
{
	return DirectX::Matrix::CreateScale(this->offset_scale_)
		* DirectX::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(this->offset_rotation_.y), DirectX::XMConvertToRadians(this->offset_rotation_.x), DirectX::XMConvertToRadians(this->offset_rotation_.z))
		* DirectX::Matrix::CreateTranslation(this->offset_position_);
}

DirectX::Matrix Transform::FinalMatrix(void)
{
	DirectX::Matrix ret;

	ret = this->OffsetMatrix() * this->TransformMatrix();

	auto parent = this->parent_;

	while (parent != nullptr)
	{
		ret *= parent->TransformMatrix();

		parent = parent->parent_;
	}

	return ret;
}

DirectX::Matrix Transform::FinalMatrixWithoutOffset(void)
{
	DirectX::Matrix ret;

	ret = this->TransformMatrix();

	auto parent = this->parent_;

	while (parent != nullptr)
	{
		ret *= parent->TransformMatrix();

		parent = parent->parent_;
	}

	return ret;
}

DirectX::Vector3 Transform::FinalPosition(void)
{
	return this->FinalMatrixWithoutOffset().Translation();
}

DirectX::Vector3 Transform::FinalRotation(void)
{
	DirectX::Quaternion q;
	DirectX::Vector3 t, s;
	auto m = this->FinalMatrixWithoutOffset();
	m.Decompose(s, q, t);

	return QuaternionToYawPitchRoll(q);
}
