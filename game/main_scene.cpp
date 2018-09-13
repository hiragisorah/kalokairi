#include "main_scene.h"

#include "rendering_system.h"
#include "camera.h"
#include "player_system.h"
#include "collision-system.h"

#include "stage_system.h"
#include "enemy-system.h"

void MainScene::Initialize(void)
{
	this->AddSystem<RenderingSystem>();
	this->AddSystem<Camera>();
	this->AddSystem<PlayerSystem>();
	this->AddSystem<CollisionSystem>();
	this->AddSystem<StageSystem>();
	this->AddSystem<EnemySystem>();
}
