#pragma once

#include "..\frame-work\SimpleMath.h"
#include <DirectXMath.h>

class Transform
{
public:
	Transform(
		DirectX::Vector3 position = { 0,0,0 },
		DirectX::Vector3 rotation = { 0,0,0 },
		DirectX::Vector3 scale = { 1,1,1 },
		DirectX::Vector3 offset_position = { 0,0,0 },
		DirectX::Vector3 offset_rotation = { 0,0,0 },
		DirectX::Vector3 offset_scale = { 1,1,1 }
	);

private:
	Transform * parent_;

public:
	Transform * const parent(void);
	void set_parent(Transform * const parent);

private:
	DirectX::Vector3 offset_position_;
	DirectX::Vector3 offset_rotation_;
	DirectX::Vector3 offset_scale_;

	DirectX::Vector3 position_;
	DirectX::Vector3 rotation_;
	DirectX::Vector3 scale_;

public:
	const DirectX::Vector3 & offset_position(void) const;
	const DirectX::Vector3 & offset_rotation(void) const;
	const DirectX::Vector3 & offset_scale(void) const;

	const DirectX::Vector3 & position(void) const;
	const DirectX::Vector3 & rotation(void) const;
	const DirectX::Vector3 & scale(void) const;

	void set_offset_position(const DirectX::Vector3 & offset_position);
	void set_offset_rotation(const DirectX::Vector3 & offset_rotation);
	void set_offset_scale(const DirectX::Vector3 & offset_scale);

	void set_position(const DirectX::Vector3 & position);
	void set_rotation(const DirectX::Vector3 & rotation);
	void set_scale(const DirectX::Vector3 & scale);

public:
	void MoveForward(const float & speed);
	void MoveSide(const float & speed);
	void RotateY(const float & speed);

public:
	DirectX::XMMATRIX TransformMatrix(void);
	DirectX::XMMATRIX OffsetMatrix(void);
	DirectX::XMMATRIX FinalMatrix(void);
};