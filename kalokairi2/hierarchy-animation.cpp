#include "hierarchy-animation.h"

HierarchyAnimation::HierarchyAnimation(void)
	: model_list_(nullptr)
{
	for (auto & anim : this->next_animation_)
		anim = nullptr;
}

void HierarchyAnimation::set_model_list(HierarchyModelList * const model_list)
{
	this->model_list_ = model_list;
}

Animation * const HierarchyAnimation::animations(const std::string & animation_name)
{
	return &this->animations_[animation_name];
}

void HierarchyAnimation::set_animation(const std::string & animation_name, const Animation & animation)
{
	this->animations_[animation_name] = animation;
}

void HierarchyAnimation::SetAnimation(const std::string & animation_name, const int & priority, const float & start_progress)
{
	this->SetAnimation(&this->animations_[animation_name], priority, start_progress);
}

void HierarchyAnimation::SetAnimation(Animation * const animation, const int & priority, const float & start_progress)
{
	if (this->next_animation_[priority] == animation) return;

	this->next_animation_[priority] = animation;

	animation->progress_ = start_progress;
}

void HierarchyAnimation::SetIntercept(const int & parts, Transform * transform)
{
	this->intercept_[parts] = transform;
}

void HierarchyAnimation::RemoveAnimation(const int & priority)
{
	this->next_animation_[priority] = nullptr;
}

void HierarchyAnimation::RemoveAnimation(const std::string & animation_name)
{
	for (auto & next_animation : this->next_animation_)
	{
		if (next_animation == &this->animations_[animation_name])
		{
			next_animation = nullptr;
		}
	}
}

void HierarchyAnimation::RemoveIntercept(const int & parts)
{
	this->intercept_.erase(parts);
}

void HierarchyAnimation::Update(void)
{
	if (this->model_list_ == nullptr) return;

	std::vector<int> parts_check;

	for (auto & intercept : this->intercept_)
	{
		auto & key = intercept.first;
		auto & transform = intercept.second;

		parts_check.emplace_back(key);

		auto model_transform = (*this->model_list_)[key].transform();

		*model_transform = *transform;
	}

	for (auto & next_animation : this->next_animation_)
	{
		if (next_animation == nullptr) continue;

		auto current_index = static_cast<int>(next_animation->progress_);
		auto frame_cnt = next_animation->frames_.size();
		auto now_progress = next_animation->progress_ - static_cast<int>(next_animation->progress_);

		auto & current_frame = next_animation->frames_[current_index];
		auto & next_frame = next_animation->frames_[(current_index + 1) % frame_cnt];

		for (auto & transform : current_frame.transforms_)
		{
			auto & key = transform.first;

			auto have = std::find(parts_check.begin(), parts_check.end(), key);

			if (have != parts_check.end()) continue;

			parts_check.emplace_back(key);

			auto & current_transform = transform.second;
			auto & next_transform = next_frame.transforms_[key];

			auto new_transform = Completion(current_transform, next_transform, now_progress);

			auto model_transform = (*this->model_list_)[key].transform();

			model_transform->set_position(new_transform.position_);
			model_transform->set_rotation(new_transform.rotation_);
			model_transform->set_scale(new_transform.scale_);
		}

		next_animation->progress_ += next_frame.speed_;

		if (static_cast<int>(next_animation->progress_) >= frame_cnt)
		{
			next_animation->progress_ -= static_cast<int>(next_animation->progress_);
			if (!next_animation->is_loop_)
			{
				next_animation = nullptr;
			}
		}
	}
}
