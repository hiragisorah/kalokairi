#pragma once

#include "..\frame-work\component.h"
#include "hierarchy-model.h"

#include <unordered_map>

class Renderer : public Seed::Component
{
private:
	std::unordered_map<int, HierarchyModel> model_list_;

private:
	MainBuffer constant_buffer_;
	
public:
	void Initialize(void) override;
	void Always(void) override;
	void Finalize(void) override;
};