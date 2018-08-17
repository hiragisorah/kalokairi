#include "hierarchy-model.h"

HierarchyModel::HierarchyModel(int primitive_id)
	: primitive_id_(primitive_id)
	, shader_id_(0)
	, transform_(new Transform)
{
}

HierarchyModel::~HierarchyModel(void)
{
	delete this->transform_;
}

const int & HierarchyModel::primitive_id(void) const
{
	return this->primitive_id_;
}

const int & HierarchyModel::shader_id(void) const
{
	return this->shader_id_;
}

void * HierarchyModel::constant_buffer(void) const
{
	return this->constant_buffer_;
}

const std::string & HierarchyModel::name(void) const
{
	return this->name_;
}

void HierarchyModel::set_primitive_id(const int & primitive_id)
{
	this->primitive_id_ = primitive_id;
}

void HierarchyModel::set_shader_id(const int & shader_id)
{
	this->shader_id_ = shader_id;
}

void HierarchyModel::set_constant_buffer(void * constant_buffer)
{
	this->constant_buffer_ = constant_buffer;
}

void HierarchyModel::set_name(const std::string & name)
{
	this->name_ = name;
}

Transform * const HierarchyModel::transform(void) const
{
	return this->transform_;
}