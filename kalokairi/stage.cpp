#include "stage.h"

void Stage::Initialize(void)
{
	this->AddComponent<Renderer>("stage.hmodel");

	this->renderer_ = this->Component<Renderer>();
}
