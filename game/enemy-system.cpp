#include "enemy-system.h"

#include "enemy.h"
#include "enemy_event.h"
#include "stage_system.h"
#include "stage_event.h"

EnemySystem::EnemySystem(void)
	: frame_cnt_(0)
	, core_transform_(nullptr)
{
}

void EnemySystem::Initialize(void)
{
	this->core_transform_ = this->owner()->System<StageSystem>()->stage()->Component<StageEvent>()->transform();
}

void EnemySystem::Update(void)
{
	if (this->frame_cnt_ % 300 == 0 || this->frame_cnt_ % 1700 == 0 || this->frame_cnt_ % 3200 == 0)
	{
		this->owner()->CreateEntity<Enemy>()->Component<EnemyEvent>()->transform()->set_position(this->core_transform_->FinalPosition() +
			DirectX::Vector3(rand()%2 == 1 ? -5.f : +12.f,0,-7.f));
		this->owner()->CreateEntity<Enemy>()->Component<EnemyEvent>()->transform()->set_position(this->core_transform_->FinalPosition() +
			DirectX::Vector3(rand()%2 == 1 ? -5.f : +12.f,0,0));
		this->owner()->CreateEntity<Enemy>()->Component<EnemyEvent>()->transform()->set_position(this->core_transform_->FinalPosition() +
			DirectX::Vector3(rand()%2 == 1 ? -5.f : +12.f,0,+7.f));
	}
	frame_cnt_++;
}
