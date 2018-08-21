#include "scene.h"

Seed::Scene::Scene(void)
	: is_alive_(true)
{
}

Seed::Scene::~Scene(void)
{
	// ��ĊJ��
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
	// �X�V�������̈�ČĂяo��
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
	// ��~�������̈�ČĂяo��
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
	// �\�񕪂𖖔��ɒǉ�
	this->entities_.insert(this->entities_.end(), this->entities_reserve_.begin(), this->entities_reserve_.end());
	this->entities_reserve_.clear();

	// �펞�����̈�ČĂяo��
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
	// �`��O�����̈�ČĂяo��
	for (auto & system : this->systems_)
		system.second->Begin(graphics);
}

void Seed::Scene::Render(Graphics & graphics)
{
	// �`�掞�����̈�ČĂяo��
	for (auto & system : this->systems_)
		system.second->Render(graphics);
}

void Seed::Scene::End(Graphics & graphics)
{
	// �`��㏈���̈�ČĂяo��
	for (auto & system : this->systems_)
		system.second->End(graphics);
}