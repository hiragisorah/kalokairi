#pragma once

#include <functional>

#include "..\frame-work\SimpleMath.h"
#include "..\frame-work\engine.h"

class Collider final
{
public:
	Collider(void);

private:
	Seed::Entity * owner_;

public:
	Seed::Entity * const owner(void) const;
	void set_owner(Seed::Entity * const owner);

private:
	std::function<void(Collider*, Collider*)> hit_callback_;

public:
	void set_hit_call_back(std::function<void(Collider*, Collider*)> hit_call_back);
	std::function<void(Collider*, Collider*)> const hit_call_back(void) const;

private:
	bool is_alive_;

private:
	DirectX::Vector3 position_;
	float radius_;

public:
	const DirectX::Vector3 & position(void) const;
	const float & radius(void) const;
	void set_position(const DirectX::Vector3 & position);
	void set_radius(const float & radius);

public:
	const bool & is_alive(void) const;
	void Destroy(void);

private:
	unsigned int type_;

public:
	void set_type(const unsigned int & type);
	const unsigned int & type(void) const;
};