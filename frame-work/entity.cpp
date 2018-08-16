#include "entity.h"

Seed::Entity::Entity(void)
	: is_alive(true)
	, scene_(nullptr)
{
}

Seed::Entity::~Entity(void)
{
	for (auto & component : this->components_)
		component.second->Finalize();

	for (auto & component : this->components_)
		delete component.second;
}

void Seed::Entity::set_scene(Scene * const scene)
{
	this->scene_ = scene;
}

Seed::Scene * const Seed::Entity::scene(void)
{
	return this->scene_;
}

void Seed::Entity::Destroy(void)
{
	this->is_alive = false;
}

const bool & Seed::Entity::IsAlive(void)
{
	return this->is_alive;
}

void Seed::Entity::Update(void)
{
	for (auto & component : this->components_)
		component.second->Update();
}

void Seed::Entity::Pause(void)
{
	for (auto & component : this->components_)
		component.second->Pause();
}

void Seed::Entity::Always(void)
{
	for (auto & component : this->components_)
		component.second->Always();
}