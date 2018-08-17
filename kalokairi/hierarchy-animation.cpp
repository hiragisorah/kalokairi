#include "hierarchy-animation.h"

HierarchyAnimation::HierarchyAnimation(void)
	: current_animation_(nullptr)
	, next_animation_(nullptr)
	, current_index_(0)
{
}

void HierarchyAnimation::set_model_list(HierarchyModelList * const model_list)
{
	this->model_list_ = model_list;
}

void HierarchyAnimation::set_animation(const std::string & animation_name, const Animation & animation)
{
	this->animations_[animation_name] = animation;
}

void HierarchyAnimation::SetAnimation(const std::string & animation_name)
{
	this->next_animation_ = &this->animations_[animation_name];

	if (this->current_animation_ == nullptr)
		this->current_animation_ = this->next_animation_;
	
	this->check_point_.transforms_ = this->new_transform_.transforms_;

	this->is_check_point_ = true;
	this->progress_ = 0;
}

void HierarchyAnimation::Update(void)
{
	auto current_frame = &this->current_animation_->frames_[(this->current_index_ + 0) % this->current_animation_->frames_.size()];
	auto next_frame = &this->current_animation_->frames_[(this->current_index_ + 1) % this->current_animation_->frames_.size()];

	if (this->next_animation_ != this->current_animation_)
	{
		next_frame = &this->next_animation_->frames_[0];
	}

	for (auto & transform : current_frame->transforms_)
	{
		auto & key = transform.first;

		auto & next_transform = next_frame->transforms_[key];

		auto & new_transform = this->new_transform_.transforms_[key];

		if(this->is_check_point_)
		{
			new_transform = Linear(this->check_point_.transforms_[key], next_transform, this->progress_);
		}
		else
		{
			new_transform = Linear(transform.second, next_transform, this->progress_);
		}

		auto now_transform = (*this->model_list_)[transform.first].transform();

		now_transform->set_position(new_transform.position_);
		now_transform->set_rotation(new_transform.rotation_);
		now_transform->set_scale(new_transform.scale_);
	}

	this->progress_ += next_frame->speed_;

	if (this->progress_ > 1.f)
	{
		this->progress_ -= 1.f;

		this->is_check_point_ = false;

		if (this->next_animation_ != this->current_animation_)
		{
			this->current_index_ = 0;
			this->current_animation_ = this->next_animation_;
		}
		else
		{
			this->current_index_++;
		}
	}
}
