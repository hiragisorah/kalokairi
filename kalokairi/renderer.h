#pragma once

#include "..\frame-work\component.h"
#include "hierarchy-model.h"
#include "hierarchy-animation.h"
#include <unordered_map>

class Renderer : public Seed::Component
{
private:
	HierarchyModelList model_list_;
	HierarchyAnimation animation_;

private:
	std::unordered_map<int, MainBuffer> constant_buffer_;

public:
	void Initialize(void) override;
	void Update(void) override;
	void Always(void) override;
	void Finalize(void) override;

public:
	void ReadHierarchyFromFile(const std::string & file_name);
	void ReadHierarchyAnimationFromFile(const std::string & file_name);

};