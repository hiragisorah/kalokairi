#include "stage.h"
#include "stage_event.h"
void Stage::Initialize(void)
{
	this->AddComponent<Renderer>("stage3.hmodel", "stage.hanim");

	this->AddComponent<StageEvent>();

	this->renderer_ = this->Component<Renderer>();
}
