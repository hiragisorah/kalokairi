#include "main_scene.h"

#include "rendering_system.h"
#include "player_system.h"
#include "stage.h"
#include "screen.h"
#include "camera.h"

void MainScene::Initialize(void)
{
	this->AddSystem<RenderingSystem>();
	this->AddSystem<Camera>();
	this->AddSystem<PlayerSystem>();

	this->CreateEntity<Stage>();
	this->CreateEntity<Screen>();
}
