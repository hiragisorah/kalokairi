#pragma once

#include "..\frame-work\component.h"
#include "hierarchy-model.h"
#include "hierarchy-animation.h"
#include <unordered_map>

class Renderer : public Seed::Component
{
public:
	Renderer(const std::string & model_file, const std::string & animation_file = "");

private:
	std::string model_file_;
	std::string animation_file_;

private:
	HierarchyModelList model_list_;
	HierarchyAnimation * animation_;

public:
	void Initialize(void) override;
	void Update(void) override;
	void Always(void) override;
	void Finalize(void) override;

public:
	void ReadHierarchyFromFile(const std::string & file_name);
	void ReadHierarchyAnimationFromFile(const std::string & file_name);

public:
	const int Find(const std::string & model_name);

public:
	HierarchyAnimation * const animation(void);
};