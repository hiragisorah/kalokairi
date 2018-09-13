#pragma once

#include "..\frame-work\engine.h"
#include "transform.h"

class Player : public Seed::Entity
{
public:
	void Initialize(void) override;

private:
	Transform * transform_;

public:
	Transform * const transform(void) const;
};