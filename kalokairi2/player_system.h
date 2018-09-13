#pragma once

#include "..\frame-work\engine.h"
#include "player.h"

class PlayerSystem : public Seed::System
{
public:
	PlayerSystem(void);

public:
	void Initialize(void) override;

private:
	Player * player_;

public:
	Player * const player(void);
};