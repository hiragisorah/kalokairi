#pragma once

namespace Seed
{
	class Entity;

	class Component
	{
	public:
		Component(void);
		virtual ~Component(void);

	private:
		Entity * owner_;

	public:
		void set_owner(Entity * const owner);
		Entity * const owner(void);

	public:
		virtual void Initialize(void) {}
		virtual void Update(void) {}
		virtual void Pause(void) {}
		virtual void Always(void) {}
		virtual void Finalize(void) {}
	};
}