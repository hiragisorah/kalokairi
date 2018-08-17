#include "transform.h"

Transform::Transform(
	DirectX::XMFLOAT3 position,
	DirectX::XMFLOAT3 rotation,
	DirectX::XMFLOAT3 scale,
	DirectX::XMFLOAT3 offset_position,
	DirectX::XMFLOAT3 offset_rotation,
	DirectX::XMFLOAT3 offset_scale)
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

const DirectX::XMFLOAT3 & Transform::offset_position(void) const
{
	return this->offset_position_;
}

const DirectX::XMFLOAT3 & Transform::offset_rotation(void) const
{
	return this->offset_rotation_;
}

const DirectX::XMFLOAT3 & Transform::offset_scale(void) const
{
	return this->offset_scale_;
}

const DirectX::XMFLOAT3 & Transform::position(void) const
{
	return this->position_;
}

const DirectX::XMFLOAT3 & Transform::rotation(void) const
{
	return this->rotation_;
}

const DirectX::XMFLOAT3 & Transform::scale(void) const
{
	return this->scale_;
}

void Transform::set_offset_position(const DirectX::XMFLOAT3 & offset_position)
{
	this->offset_position_ = offset_position;
}

void Transform::set_offset_rotation(const DirectX::XMFLOAT3 & offset_rotation)
{
	this->offset_rotation_ = offset_rotation;
}

void Transform::set_offset_scale(const DirectX::XMFLOAT3 & offset_scale)
{
	this->offset_scale_ = offset_scale;
}

void Transform::set_position(const DirectX::XMFLOAT3 & position)
{
	this->position_ = position;
}

void Transform::set_rotation(const DirectX::XMFLOAT3 & rotation)
{
	this->rotation_ = rotation;
}

void Transform::set_scale(const DirectX::XMFLOAT3 & scale)
{
	this->scale_ = scale;
}

DirectX::XMMATRIX Transform::TransformMatrix(void)
{
	return DirectX::XMMatrixScaling(this->scale_.x, this->scale_.y, this->scale_.z)
		* DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(this->rotation_.x), DirectX::XMConvertToRadians(this->rotation_.y), DirectX::XMConvertToRadians(this->rotation_.z))
		* DirectX::XMMatrixTranslation(this->position_.x, this->position_.y, this->position_.z);
}

DirectX::XMMATRIX Transform::OffsetMatrix(void)
{
	return DirectX::XMMatrixScaling(this->offset_scale_.x, this->offset_scale_.y, this->offset_scale_.z)
		* DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(this->offset_rotation_.x), DirectX::XMConvertToRadians(this->offset_rotation_.y), DirectX::XMConvertToRadians(this->offset_rotation_.z))
		* DirectX::XMMatrixTranslation(this->offset_position_.x, this->offset_position_.y, this->offset_position_.z);
}

DirectX::XMMATRIX Transform::FinalMatrix(void)
{
	DirectX::XMMATRIX ret;

	ret = this->OffsetMatrix() * this->TransformMatrix();

	auto parent = this->parent_;

	while (parent != nullptr)
	{
		ret *= parent->TransformMatrix();

		parent = parent->parent_;
	}

	return ret;
}
