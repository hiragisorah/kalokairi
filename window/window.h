#pragma once

#include <string>

namespace Seed
{
	class Window
	{
	public:
		Window(void);
		~Window(void);

	public:
		virtual const bool Initalize(const std::string & caption = "Window Title.", const unsigned int & width = 1280U, const unsigned int & height = 720U);
		virtual const bool Run(void);
		virtual const bool Finalize(void);

	private:
		virtual const unsigned int & get_width(void);
		virtual const unsigned int & get_height(void);
		virtual void * const get_hwnd(void);

	public:
		virtual const std::string & get_caption(void);
		template<class _Type> const _Type get_width(void) { return static_cast<_Type>(this->get_width()); }
		template<class _Type> const _Type get_height(void) { return static_cast<_Type>(this->get_height()); }
		template<class _Type> const _Type get_hwnd(void) { return static_cast<_Type>(this->get_hwnd()); }

	private:
		class Impl;
		Impl * impl_;
	};
}