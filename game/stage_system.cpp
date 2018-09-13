#include "stage_system.h"
#include "stage_event.h"

void StageSystem::Initialize(void)
{
	this->stage_ = this->owner()->CreateEntity<Stage>();
}

Stage * const StageSystem::stage(void)
{
	return this->stage_;
}

const bool StageSystem::is_end(void)
{
	return this->stage_->Component<StageEvent>()->is_end();
}
