#pragma once

#include "scene.h"
#include "..\graphics\graphics.h"

namespace Seed
{
	class Engine final
	{
	public:
		Engine(Graphics & graphics);
		~Engine(void);

	public:
		template<class _Scene, class ... Args> const bool Initialize(const Args &... args)
		{
			this->current_scene_ = new _Scene(args ...);
			this->current_scene_->set_engine(this);

			return Initialize();
		}
		const bool Initialize(void);


	private:
		Scene * current_scene_;
		Scene * next_scene_;

	public:
		template<class _Scene, class ... Args> void ChangeScene(const Args &... args)
		{
			this->next_scene_ = new _Scene(args ...);
			this->next_scene_->set_engine(this);
		}

	private:
		bool pause_;

	public:
		void Pause(void);
		void Resume(void);

	private:
		Graphics & graphics_;

	public:
		Graphics * const graphics(void) const;

	public:
		const bool Run(void);
		const bool ProcessScene(void);
	};
}