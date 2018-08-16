#pragma once

#include <unordered_map>

#include "system.h"
#include "entity.h"

namespace Seed
{
	class Engine;

	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

	private:
		bool is_alive_;
		
	public:
		void Destroy(void);
		const bool IsAlive(void);

	private:
		Engine * engine_;

	public:
		void set_engine(Engine * const engine);
		Engine * const engine(void) const;
	
	private:
		std::vector<Seed::Entity*> entities_reserve_;
		std::vector<Seed::Entity*> entities_;

	public:
		template<class _Entity, class ... Args> _Entity * const CreateEntity(const Args &... args)
		{
			auto entity = new _Entity(args ...);

			this->entities_reserve_.emplace_back(entity);

			entity->set_scene(this);
			entity->Initialize();

			return entity;
		}

	private:
		std::unordered_map<std::type_index, System*> systems_;

	public:
		template<class _System, class ... Args> void AddSystem(const Args &... args)
		{
			auto & system = this->systems_[typeid(_System)] = new _System(args ...);

			system->set_owner(this);
			system->Initialize();
		}
		template<class _System> _System * const System(void)
		{
			auto system = this->systems_[typeid(_System)];
			return static_cast<_System*>(system);
		}
		template<class _System> void RemoveSystem(void)
		{
			auto & system = this->systems_[typeid(_System)];

			system->Finalize();

			delete system;

			this->systems_.erase(typeid(_System));
		}

	public:
		void Update(void);
		void Pause(void);
		void Always(void);
		void Begin(Graphics & graphics);
		void Render(Graphics & graphics);
		void End(Graphics & graphics);

	public:
		virtual void Initialize(void) = 0;
		virtual void Finalize(void) {};
	};
}