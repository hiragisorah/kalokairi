#include "collider.h"

Collider::Collider(void)
	: is_alive_(true)
	, type_(0)
{
}

Seed::Entity * const Collider::owner(void) const
{
	return this->owner_;
}

void Collider::set_owner(Seed::Entity * const owner)
{
	this->owner_ = owner;
}

void Collider::set_hit_call_back(std::function<void(Collider*, Collider*)> hit_call_back)
{
	this->hit_callback_ = hit_call_back;
}

std::function<void(Collider*, Collider*)> const Collider::hit_call_back(void) const
{
	return this->hit_callback_;
}

const DirectX::Vector3 & Collider::position(void) const
{
	return this->position_;
}

const float & Collider::radius(void) const
{
	return this->radius_;
}

void Collider::set_position(const DirectX::Vector3 & position)
{
	this->position_ = position;
}

void Collider::set_radius(const float & radius)
{
	this->radius_ = radius;
}

const bool & Collider::is_alive(void) const
{
	return this->is_alive_;
}

void Collider::Destroy(void)
{
	this->is_alive_ = false;
}

void Collider::set_type(const unsigned int & type)
{
	this->type_ = type;
}

const unsigned int & Collider::type(void) const
{
	return this->type_;
}
