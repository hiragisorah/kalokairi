#include "main_scene.h"

#include "rendering_system.h"
#include "player.h"

void MainScene::Initialize(void)
{
	this->AddSystem<RenderingSystem>();

	this->CreateEntity<Player>();
}
