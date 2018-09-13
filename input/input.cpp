#include "input.h"

static std::unordered_map<unsigned int, Seed::Input::KeyState> _keys;
static std::unordered_map<unsigned int, bool> * _key_map = nullptr;
static std::unordered_map<unsigned int, bool> _old_keys;
static std::unordered_map<unsigned int, unsigned int> _t_keys;

const bool Seed::Input::Update(void)
{
	for (auto & key : *_key_map)
	{
		auto & new_status = key.second;
		auto & old_status = _old_keys[key.first];
		auto & t_status = _t_keys[key.first];

		if (t_status) t_status++;

		if (t_status > 20)
			t_status = 0;

		if (!old_status && !new_status) _keys[key.first] = Seed::Input::KeyState::None;
		if (!old_status && new_status) _keys[key.first] = Seed::Input::KeyState::Trigger;
		if (old_status && new_status) _keys[key.first] = Seed::Input::KeyState::Press;
		if (old_status && !new_status) _keys[key.first] = Seed::Input::KeyState::Release;

		if (!old_status && new_status && t_status) _keys[key.first] = Seed::Input::KeyState::Repeat;
		if (!old_status && new_status) t_status = 1;

		old_status = new_status;
	}

	return true;
}

bool Seed::Input::Trigger(const unsigned int & key)
{
	return _keys[key] == Seed::Input::KeyState::Trigger || _keys[key] == Seed::Input::KeyState::Repeat;
}

bool Seed::Input::Release(const unsigned int & key)
{
	return _keys[key] == Seed::Input::KeyState::Release;
}

bool Seed::Input::Repeat(const unsigned int & key)
{
	return _keys[key] == Seed::Input::KeyState::Repeat;
}

bool Seed::Input::Press(const unsigned int & key)
{
	return _keys[key] == Seed::Input::KeyState::Press;
}

void Seed::Input::SetKeyMap(std::unordered_map<unsigned int, bool> * key_map)
{
	_key_map = key_map;
}
