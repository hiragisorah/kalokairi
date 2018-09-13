#pragma once

#include <unordered_map>

namespace Seed
{
	namespace Input
	{
		enum class KeyState
		{
			None,
			Trigger,
			Press,
			Release,
			Repeat,
		};

		const bool Update(void);
		bool Trigger(const unsigned int & key);
		bool Release(const unsigned int & key);
		bool Repeat(const unsigned int & key);
		bool Press(const unsigned int & key);

		void SetKeyMap(std::unordered_map<unsigned int, bool> * key_map);
	}
}