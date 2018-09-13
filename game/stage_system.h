#pragma once

#include "stage.h"

class StageSystem : public Seed::System
{
public:
	void Initialize(void) override;

private:
	Stage * stage_;

public:
	Stage * const stage(void);

	const bool is_end(void);
};