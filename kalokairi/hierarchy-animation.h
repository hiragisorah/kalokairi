#pragma once

#include <unordered_map>

#include "hierarchy-model.h"
#include <algorithm>

struct AnimationTransform
{
	AnimationTransform(void)
		: position_(DirectX::Vector3::Zero)
		, rotation_(DirectX::Vector3::Zero)
		, scale_(DirectX::Vector3(1, 1, 1))
	{}

	DirectX::Vector3 position_;
	DirectX::Vector3 rotation_;
	DirectX::Vector3 scale_;
};

#undef min

static AnimationTransform Linear(AnimationTransform & a, AnimationTransform & b, float progress)
{
	AnimationTransform ret = a;

	ret.position_.x = a.position_.x + (b.position_.x - a.position_.x) * progress;
	ret.position_.y = a.position_.y + (b.position_.y - a.position_.y) * progress;
	ret.position_.z = a.position_.z + (b.position_.z - a.position_.z) * progress;

	ret.rotation_.x = a.rotation_.x + (b.rotation_.x - a.rotation_.x) * progress;
	ret.rotation_.y = a.rotation_.y + (b.rotation_.y - a.rotation_.y) * progress;
	ret.rotation_.z = a.rotation_.z + (b.rotation_.z - a.rotation_.z) * progress;

	ret.scale_.x = a.scale_.x + (b.scale_.x - a.scale_.x) * progress;
	ret.scale_.y = a.scale_.y + (b.scale_.y - a.scale_.y) * progress;
	ret.scale_.z = a.scale_.z + (b.scale_.z - a.scale_.z) * progress;

	return ret;
}

constexpr float default_distance = 10.f;
constexpr float default_rotation = 50.f;
constexpr float default_scale = 10.f;

static AnimationTransform Completion(const AnimationTransform & a, const AnimationTransform & b, const float & speed, bool & check)
{
	AnimationTransform ret;

	auto dist = DirectX::Vector3::Distance(a.position_, b.position_);
	auto diff = b.position_ - a.position_;

	auto x = std::min((default_distance * speed) / dist, 1.f);

	ret.position_ = a.position_ + diff * x;

	if (fabsf(dist) > 0.001f) check = false;

	dist = DirectX::Vector3::Distance(a.rotation_, b.rotation_);
	diff = b.rotation_ - a.rotation_;

	x = std::min((default_rotation * speed) / dist, 1.f);

	ret.rotation_ = a.rotation_ + diff * x;

	if (fabsf(dist) > 0.001f) check = false;

	dist = DirectX::Vector3::Distance(a.scale_, b.scale_);
	diff = b.scale_ - a.scale_;

	x = std::min((default_scale * speed) / dist, 1.f);

	ret.scale_ = a.scale_ + diff * x;

	if (fabsf(dist) > 0.001f) check = false;

	return ret;
}

struct AnimationFrame
{
	AnimationFrame(void)
		: speed_(0.02f)
	{}

	std::unordered_map<int, AnimationTransform> transforms_;

	float speed_;
};

struct Animation
{
	Animation(void)
		: current_index_(0)
		, is_loop_(true)
	{}

	std::vector<AnimationFrame> frames_;
	int current_index_;
	bool is_loop_;
};

class HierarchyAnimation
{
public:
	HierarchyAnimation(void);

private:
	HierarchyModelList * model_list_;

public:
	void set_model_list(HierarchyModelList * const model_list);

private:
	std::unordered_map<std::string, Animation> animations_;

public:
	void set_animation(const std::string & animation_name, const Animation & animation);

public:
	void SetAnimation(const std::string & animation_name, const int & priority);
	void SetAnimation(Animation * const animation, const int & priority);

private:
	Animation * next_animation_[10];

public:
	void Update(void);
};