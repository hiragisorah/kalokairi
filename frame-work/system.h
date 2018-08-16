#pragma once

#include "..\graphics\graphics.h"

namespace Seed
{
	class Scene;

	class System
	{
	public:
		System(void);
		virtual ~System(void);

	private:
		Scene * owner_;

	public:
		void set_owner(Scene * const owner);
		Scene * const owner(void) const;

	public:
		virtual void Initialize(void) {}
		virtual void Update(void) {}
		virtual void Pause(void) {}
		virtual void Always(void) {}
		virtual void Begin(Graphics &) {}
		virtual void Render(Graphics &) {}
		virtual void End(Graphics &) {}
		virtual void Finalize(void) {}
	};
}