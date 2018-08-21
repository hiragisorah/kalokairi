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

static AnimationTransform Completion(const AnimationTransform & a, const AnimationTransform & b, const float & progress)
{
	AnimationTransform ret;

	//DirectX::Quaternion q1, q2;

	//q1 = DirectX::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(a.rotation_.y), DirectX::XMConvertToRadians(a.rotation_.x), DirectX::XMConvertToRadians(a.rotation_.z));
	//q2 = DirectX::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(b.rotation_.y), DirectX::XMConvertToRadians(b.rotation_.x), DirectX::XMConvertToRadians(b.rotation_.z));

	//ret.rotation_ = QuaternionToYawPitchRoll(DirectX::Quaternion::Slerp(q1, q2, progress));

	ret.position_ = DirectX::Vector3::Lerp(a.position_, b.position_, progress);
	ret.rotation_ = DirectX::Vector3::Lerp(a.rotation_, b.rotation_, progress);
	ret.scale_ = DirectX::Vector3::Lerp(a.scale_, b.scale_, progress);

	return ret;
}

static AnimationTransform Completion(const Transform & a, const Transform & b, const float & progress)
{
	AnimationTransform ret;

	ret.position_ = DirectX::Vector3::Lerp(a.position(), b.position(), progress);
	ret.rotation_ = DirectX::Vector3::Lerp(a.rotation(), b.rotation(), progress);
	ret.scale_ = DirectX::Vector3::Lerp(a.scale(), b.scale(), progress);

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
		: is_loop_(true)
		, progress_(0)
	{}

	std::vector<AnimationFrame> frames_;
	bool is_loop_;

	float progress_;
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
	Animation * const animations(const std::string & animation_name);

public:
	void set_animation(const std::string & animation_name, const Animation & animation);

public:
	void SetAnimation(const std::string & animation_name, const int & priority, const float & start_progress = 0.f);
	void SetAnimation(Animation * const animation, const int & priority, const float & start_progress = 0.f);
	void SetIntercept(const int & parts, Transform * transform);
	void RemoveAnimation(const int & priority);
	void RemoveAnimation(const std::string & animation_name);
	void RemoveIntercept(const int & parts);

private:
	Animation * next_animation_[10];
	std::unordered_map<int, Transform*> intercept_;

public:
	void Update(void);
};