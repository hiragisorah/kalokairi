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
	void set_position(const DirectX::Vector3 & position, const float & progress);
	void set_fixed_rotation(const DirectX::Vector3 & rotation);
	void set_rotation(const DirectX::Vector3 & rotation);
	void set_rotation(const DirectX::Vector3 & rotation, const float & progress);
	void set_scale(const DirectX::Vector3 & scale);
	void set_scale(const DirectX::Vector3 & scale, const float & progress);

public:
	void MoveForward(const float & speed);
	void MoveLeft(const float & speed);
	void MoveRight(const float & speed);

	void RotateX(const float & speed);
	void RotateY(const float & speed);
	void RotateZ(const float & speed);

public:
	void Update(void);

public:
	DirectX::Matrix TransformMatrix(void);
	DirectX::Matrix OffsetMatrix(void);
	DirectX::Matrix FinalMatrix(void);
	DirectX::Matrix FinalMatrixWithoutOffset(void);
	DirectX::Vector3 FinalPosition(void);
	DirectX::Vector3 FinalRotation(void);
};