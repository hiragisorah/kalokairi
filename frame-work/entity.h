#pragma once

#include <unordered_map>
#include <typeindex>

#include "component.h"

namespace Seed
{
	class Scene;

	class Entity
	{
	public:
		Entity(void);
		virtual ~Entity(void);

	private:
		Scene * scene_;

	public:
		void set_scene(Scene * const scene);
		Scene * const scene(void);

	private:
		std::unordered_map<std::type_index, Component*> components_;

	public:
		template<class _Component, class ... Args> void AddComponent(const Args &... args)
		{
			auto & component = this->components_[typeid(_Component)] = new _Component(args ...);
			component->set_owner(this);
			component->Initialize();
		}
		template<class _Component> _Component * const Component(void)
		{
			auto & component = this->components_[typeid(_Component)];
			return static_cast<_Component*>(component);
		}
		template<class _Component> void RemoveComponent(void)
		{
			auto & component = this->components_[typeid(_Component)];
			component->Finalize();
			delete component;
			this->components_.erase(typeid(_Component));
		}

	private:
		bool is_alive;

	public:
		void Destroy(void);
		const bool & IsAlive(void);

	public:
		void Update(void);
		void Pause(void);
		void Always(void);

	public:
		virtual void Initialize(void) = 0;
		virtual void Finalize(void) {};
	};
}