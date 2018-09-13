#include "title-scene.h"

#include "title-rendering-system.h"

void TitleScene::Initialize(void)
{
	this->AddSystem<TitleRenderingSystem>();
}
