#include "result-scene.h"

#include "result-rendering-system.h"

void ResultScene::Initialize(void)
{
	this->AddSystem<ResultRenderingSystem>();
}
