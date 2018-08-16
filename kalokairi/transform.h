#pragma once

#include <DirectXMath.h>

class Transform
{
public:
	Transform(
		DirectX::XMFLOAT3 position = { 0,0,0 },
		DirectX::XMFLOAT3 rotation = { 0,0,0 },
		DirectX::XMFLOAT3 scale = { 1,1,1 },
		DirectX::XMFLOAT3 offset_position = { 0,0,0 },
		DirectX::XMFLOAT3 offset_rotation = { 0,0,0 },
		DirectX::XMFLOAT3 offset_scale = { 1,1,1 }
	);

private:
	Transform * parent_;

public:
	Transform * const parent(void);
	void set_parent(Transform * const parent);

private:
	DirectX::XMFLOAT3 offset_position_;
	DirectX::XMFLOAT3 offset_rotation_;
	DirectX::XMFLOAT3 offset_scale_;

	DirectX::XMFLOAT3 position_;
	DirectX::XMFLOAT3 rotation_;
	DirectX::XMFLOAT3 scale_;

public:
	const DirectX::XMFLOAT3 & offset_position(void) const;
	const DirectX::XMFLOAT3 & offset_rotation(void) const;
	const DirectX::XMFLOAT3 & offset_scale(void) const;

	const DirectX::XMFLOAT3 & position(void) const;
	const DirectX::XMFLOAT3 & rotation(void) const;
	const DirectX::XMFLOAT3 & scale(void) const;

	void set_offset_position(const DirectX::XMFLOAT3 & offset_position);
	void set_offset_rotation(const DirectX::XMFLOAT3 & offset_rotation);
	void set_offset_scale(const DirectX::XMFLOAT3 & offset_scale);

	void set_position(const DirectX::XMFLOAT3 & position);
	void set_rotation(const DirectX::XMFLOAT3 & rotation);
	void set_scale(const DirectX::XMFLOAT3 & scale);

public:
	DirectX::XMMATRIX TransformMatrix(void);
	DirectX::XMMATRIX OffsetMatrix(void);
	DirectX::XMMATRIX FinalMatrix(void);
};