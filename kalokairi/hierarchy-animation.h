#pragma once

#include <unordered_map>

#include "hierarchy-model.h"

struct AnimationTransform
{
	AnimationTransform(void)
		: position_({ 0,0,0 })
		, rotation_({ 0,0,0 })
		, scale_({ 1,1,1 })
	{}

	DirectX::XMFLOAT3 position_;
	DirectX::XMFLOAT3 rotation_;
	DirectX::XMFLOAT3 scale_;
};

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
	std::vector<AnimationFrame> frames_;
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
	void SetAnimation(const std::string & animation_name);

private:
	AnimationFrame check_point_;
	AnimationFrame new_transform_;
	Animation * current_animation_;
	Animation * next_animation_;

	bool is_check_point_;

	int current_index_;
	float progress_;

public:
	void Update(void);
};