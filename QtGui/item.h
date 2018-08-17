#pragma once

#include <DirectXMath.h>

#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>

struct ItemData
{
	static unsigned int cnt;

	ItemData(void)
		: self(cnt)
		, parent(-1)
		, position({ 0,0,0 })
		, rotation({ 0,0,0 })
		, scale({ 1,1,1 })
		, offset_position({ 0,0,0 })
		, offset_rotation({ 0,0,0 })
		, offset_scale({ 1,1,1 })
		, primitive_id(-1)
		, primitive_type(0)
		, plane_div_x(1)
		, plane_div_y(1)
		, plane_size({ 0.5f, 0.5f })
		, box_size({ .1f,.1f,.1f })
		, sphere_tessellation(16)
		, sphere_diameter(1.f)
		, geosphere_tessellation(3)
		, geosphere_diameter(1.f)
		, capsule_tessellation(18)
		, capsule_diameter(1.f)
		, capsule_p1({ 0,-.5f,0 })
		, capsule_p2({ 0,+.5f,0 })
	{}

	int self;

	int parent;

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	DirectX::XMFLOAT3 offset_position;
	DirectX::XMFLOAT3 offset_rotation;
	DirectX::XMFLOAT3 offset_scale;

	int primitive_id;

	unsigned int primitive_type;

	unsigned int plane_div_x;
	unsigned int plane_div_y;

	DirectX::XMFLOAT2 plane_size;

	DirectX::XMFLOAT3 box_size;

	unsigned int sphere_tessellation;
	float sphere_diameter;

	unsigned int geosphere_tessellation;
	float geosphere_diameter;

	DirectX::XMFLOAT3 capsule_p1;
	DirectX::XMFLOAT3 capsule_p2;

	unsigned int capsule_tessellation;
	float capsule_diameter;

	std::string name;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(self, parent,
			position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z,
			offset_position.x, offset_position.y, offset_position.z, offset_rotation.x, offset_rotation.y, offset_rotation.z, offset_scale.x, offset_scale.y, offset_scale.z,
			-1, primitive_type, plane_div_x, plane_div_y, plane_size.x, plane_size.y, box_size.x, box_size.y,
			sphere_tessellation, sphere_diameter, geosphere_tessellation, geosphere_diameter,
			capsule_p1.x, capsule_p1.y, capsule_p1.z, capsule_p2.x, capsule_p2.y, capsule_p2.z,
			capsule_tessellation, capsule_diameter, name);
	}
};

struct AnimData
{
	AnimData(void)
		: self(cnt)
	{
		frames.resize(5);
		speed.resize(5);

		for (auto & sp : speed)
			sp = 0.01f;
	}

	static unsigned int cnt;

	int self;

	std::string name;

	std::vector<std::unordered_map<int, ItemData>> frames;
	std::vector<float> speed;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(self, name, frames, speed);
	}
};