#include "main_scene.h"

#include "rendering_system.h"
#include "player.h"
#include "stage.h"
#include "screen.h"

void MainScene::Initialize(void)
{
	this->AddSystem<RenderingSystem>();

	this->CreateEntity<Stage>();
	this->CreateEntity<Player>();
	this->CreateEntity<Screen>();
}
