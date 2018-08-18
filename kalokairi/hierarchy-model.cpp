#include "hierarchy-model.h"

HierarchyModel::HierarchyModel(int primitive_id)
	: primitive_id_(primitive_id)
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

const std::string & HierarchyModel::name(void) const
{
	return this->name_;
}

void HierarchyModel::set_primitive_id(const int & primitive_id)
{
	this->primitive_id_ = primitive_id;
}

void HierarchyModel::set_name(const std::string & name)
{
	this->name_ = name;
}

Transform * const HierarchyModel::transform(void) const
{
	return this->transform_;
}