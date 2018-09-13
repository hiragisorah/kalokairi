#pragma once

#include "transform.h"
#include <unordered_map>

struct MainBuffer
{
	DirectX::XMMATRIX world_;
	DirectX::XMMATRIX view_;
	DirectX::XMMATRIX projection_;

	DirectX::XMFLOAT3A eye_;
};

class HierarchyModel
{
public:
	HierarchyModel(int primitive_id = -1);
	virtual ~HierarchyModel(void);

private:
	int primitive_id_;
	std::string name_;

public:
	const int & primitive_id(void) const;
	const std::string & name(void) const;
	
	void set_primitive_id(const int & primitive_id);
	void set_name(const std::string & name);

private:
	Transform * transform_;
	DirectX::Vector4 diffuse_;

public:
	Transform * const transform(void) const;
	const DirectX::Vector4 & diffuse(void);
	void set_diffuse(const DirectX::Vector4 & diffuse);
};

using HierarchyModelList = std::unordered_map<int, HierarchyModel>;