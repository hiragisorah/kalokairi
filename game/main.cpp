#include "..\input\input.h"
#include "..\window\window.h"
#include "..\graphics\graphics.h"
#include "..\frame-work\engine.h"

#include "main_scene.h"
#include "title-scene.h"

#include <Windows.h>
#include <chrono>

constexpr const unsigned int fps = 60;
constexpr const float time_per_frame = 1000.f / fps;

static const bool FpsFixed(void)
{
	static auto start = std::chrono::system_clock::now();

	while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() < time_per_frame);

	start = std::chrono::system_clock::now();

	return true;
}

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Seed::Window window;
	Seed::Graphics graphics;
	Seed::Engine engine(graphics);

	window.Initalize("test", 1280U, 720U);
	graphics.Initialize(window.get_hwnd<void*>(), window.get_width<unsigned int>(), window.get_height<unsigned int>());
	engine.Initialize<TitleScene>();
	
	while (FpsFixed() && Seed::Input::Update() && window.Run() && engine.Run() && graphics.Run());

	graphics.Finalize();
	window.Finalize();

	return 0;
}