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

void HierarchyAnimation::set_animation(const std::string & animation_name, const Animation & animation)
{
	this->animations_[animation_name] = animation;
}

void HierarchyAnimation::SetAnimation(const std::string & animation_name, const int & priority)
{
	this->SetAnimation(&this->animations_[animation_name], priority);
}

void HierarchyAnimation::SetAnimation(Animation * const animation, const int & priority)
{
	if (this->next_animation_[priority] == animation) return;

	this->next_animation_[priority] = animation;

	animation->current_index_ = 0;
}

void HierarchyAnimation::Update(void)
{
	if (this->model_list_ == nullptr) return;

	std::vector<int> parts_check;

	for (auto & next_animation : this->next_animation_)
	{
		if (next_animation == nullptr) continue;

		auto check = true;

		auto & next_frame = next_animation->frames_[next_animation->current_index_];

		for (auto & transform : next_frame.transforms_)
		{
			auto & key = transform.first;

			auto have = std::find(parts_check.begin(), parts_check.end(), key);

			if (have != parts_check.end()) continue;

			parts_check.emplace_back(key);

			auto & next_transform = transform.second;

			auto model_transform = (*this->model_list_)[transform.first].transform();

			AnimationTransform current_transform;
			current_transform.position_ = model_transform->position();
			current_transform.rotation_ = model_transform->rotation();
			current_transform.scale_ = model_transform->scale();

			auto new_transform = Completion(current_transform, next_transform, next_frame.speed_, check);

			model_transform->set_position(new_transform.position_);
			model_transform->set_rotation(new_transform.rotation_);
			model_transform->set_scale(new_transform.scale_);
		}

		if (check)
		{
			next_animation->current_index_++;

			if (next_animation->current_index_ >= next_animation->frames_.size())
			{
				next_animation->current_index_ = 0;
				if (!next_animation->is_loop_)
				{
					next_animation = nullptr;
				}
			}
		}
	}
}
