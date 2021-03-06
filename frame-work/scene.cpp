#include "scene.h"

Seed::Scene::Scene(void)
	: is_alive_(true)
{
}

Seed::Scene::~Scene(void)
{
	// 一斉開放
	for (auto & system : this->systems_)
		delete system.second;

	for (auto & entity : this->entities_)
		delete entity;
}

void Seed::Scene::Destroy(void)
{
	this->is_alive_ = false;
}

const bool Seed::Scene::IsAlive(void)
{
	return this->is_alive_;
}

void Seed::Scene::set_engine(Seed::Engine * const engine)
{
	this->engine_ = engine;
}

Seed::Engine * const Seed::Scene::engine(void) const
{
	return this->engine_;
}

void Seed::Scene::Update(void)
{
	// 更新時処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->Update();

	for (auto itr = this->entities_.begin(); itr != this->entities_.end();)
		if ((*itr)->IsAlive())
		{
			(*itr)->Update();
			++itr;
		}
		else
		{
			delete *itr;
			itr = this->entities_.erase(itr);
		}
}

void Seed::Scene::Pause(void)
{
	// 停止時処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->Pause();

	for (auto itr = this->entities_.begin(); itr != this->entities_.end();)
		if ((*itr)->IsAlive())
		{
			(*itr)->Update();
			++itr;
		}
		else
		{
			delete *itr;
			itr = this->entities_.erase(itr);
		}
}

void Seed::Scene::Always(void)
{
	// 予約分を末尾に追加
	this->entities_.insert(this->entities_.end(), this->entities_reserve_.begin(), this->entities_reserve_.end());
	this->entities_reserve_.clear();

	// 常時処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->Always();

	for (auto itr = this->entities_.begin(); itr != this->entities_.end();)
		if ((*itr)->IsAlive())
		{
			(*itr)->Always();
			++itr;
		}
		else
		{
			delete *itr;
			itr = this->entities_.erase(itr);
		}
}

void Seed::Scene::Begin(Graphics & graphics)
{
	// 描画前処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->Begin(graphics);
}

void Seed::Scene::Render(Graphics & graphics)
{
	// 描画時処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->Render(graphics);
}

void Seed::Scene::End(Graphics & graphics)
{
	// 描画後処理の一斉呼び出し
	for (auto & system : this->systems_)
		system.second->End(graphics);
}