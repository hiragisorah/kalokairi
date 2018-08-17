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
	int shader_id_;
	void * constant_buffer_;
	std::string name_;

public:
	const int & primitive_id(void) const;
	const int & shader_id(void) const;
	void * constant_buffer(void) const;
	const std::string & name(void) const;
	
	void set_primitive_id(const int & primitive_id);
	void set_shader_id(const int & shader_id);
	void set_constant_buffer(void * constant_buffer);
	void set_name(const std::string & name);

private:
	Transform * transform_;

public:
	Transform * const transform(void) const;
};

using HierarchyModelList = std::unordered_map<int, HierarchyModel>;