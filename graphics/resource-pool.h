#pragma once

#include <memory>
#include <vector>

template<class _Data>
class ResourcePool
{
private:
	std::vector<std::unique_ptr<_Data>> pool_;
	std::vector<unsigned int> reuse_;

public:
	const std::unique_ptr<_Data> & Get(const unsigned int & key)
	{
		return this->pool_[key];
	}

	const unsigned int Load(std::unique_ptr<_Data> & data)
	{
		if (this->reuse_.size())
		{
			auto key = this->reuse_.back();
			this->reuse_.pop_back();
			this->pool_[key] = std::move(data);
			return key;
		}

		this->pool_.emplace_back(std::move(data));

		return static_cast<unsigned int>(pool_.size() - 1);
	}
	void Unload(const unsigned int & key)
	{
		this->pool_[key].reset(nullptr);
		
		this->reuse_.emplace_back(key);
	}
};