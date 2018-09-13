#include "window.h"

#define WIN32_LEAD_AND_MEAN
#include <Windows.h>
#include <unordered_map>
#include "..\input\input.h"

static std::unordered_map<unsigned int, bool> _key_map;

static LRESULT __stdcall WndProc(HWND hwnd, UINT i_msg, WPARAM w_param, LPARAM l_param)
{
	switch (i_msg)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
		_key_map[w_param] = true;
		break;
	case WM_KEYUP:
		_key_map[w_param] = false;
		break;
	case WM_SYSKEYUP: break;
	default:
		return DefWindowProc(hwnd, i_msg, w_param, l_param);
	}
	return 0;
}

class Seed::Window::Impl
{
public:
	Impl(void)
		: caption_("Window Title")
		, width_(1280U)
		, height_(720U)
		, hwnd_(nullptr)
		, hinstance_(nullptr)
	{}

public:
	const bool Initalize(const std::string & caption, const unsigned int & width, const unsigned int & height)
	{
		Input::SetKeyMap(&_key_map);

		caption_ = caption;
		width_ = width;
		height_ = height;

		{// ハンドル取得
			hinstance_ = GetModuleHandleA(nullptr);
		}

		{// ウィンドウクラスの登録
			WNDCLASSEX  wc;
			memset(&wc, 0, sizeof(wc));
			wc.cbSize = sizeof(wc);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WndProc;
			wc.hInstance = hinstance_;
			wc.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			wc.lpszClassName = get_caption().c_str();
			wc.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);
			RegisterClassExA(&wc);
		}

		{// ウィンドウの大きさの再調整、中央配置計算
			RECT rc;
			rc.left = 0;
			rc.top = 0;
			rc.right = static_cast<long>(this->width_);
			rc.bottom = static_cast<long>(this->height_);

			AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, true, 0);

			int w = rc.right - rc.left;
			int h = rc.bottom - rc.top;

			RECT rc_desk;
			GetWindowRect(GetDesktopWindow(), &rc_desk);

			int x = rc_desk.right / 2 - w / 2;
			int y = rc_desk.bottom / 2 - h / 2;

			{// ウィンドウの生成、表示
				hwnd_ = CreateWindowExA(0, get_caption().c_str(), get_caption().c_str(), WS_OVERLAPPEDWINDOW,
					x, y, w, h, 0, 0, hinstance_, 0);

				ShowWindow(hwnd_, SW_SHOW);
			}
		}

		return true;
	}
	const bool Run(void)
	{
		return MessageLoop();
	}
	const bool Finalize(void)
	{
		return true;
	}

private:
	std::string caption_;
	unsigned int width_;
	unsigned int height_;
	HWND hwnd_;
	HINSTANCE hinstance_;

public:
	const unsigned int & get_width(void)
	{
		return this->width_;
	}
	const unsigned int & get_height(void)
	{
		return this->height_;
	}
	const std::string & get_caption(void)
	{
		return this->caption_;
	}
	void * const get_hwnd(void)
	{
		return this->hwnd_;
	}

private:
	const bool MessageLoop(void)
	{
		MSG msg = { 0 };
		memset(&msg, 0, sizeof(msg));

		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			if (msg.message == WM_QUIT) return false;
		}
		return true;
	}
};

Seed::Window::Window(void)
	: impl_(new Window::Impl)
{
}

Seed::Window::~Window(void)
{
	delete this->impl_;
}

const bool Seed::Window::Initalize(const std::string & caption, const unsigned int & width, const unsigned int & height)
{
	return this->impl_->Initalize(caption, width, height);
}

const bool Seed::Window::Run(void)
{
	return this->impl_->Run();
}

const bool Seed::Window::Finalize(void)
{
	return this->impl_->Finalize();
}

const std::string & Seed::Window::get_caption(void)
{
	return this->impl_->get_caption();
}

const unsigned int & Seed::Window::get_width(void)
{
	return this->impl_->get_width();
}

const unsigned int & Seed::Window::get_height(void)
{
	return this->impl_->get_height();
}

void * const Seed::Window::get_hwnd(void)
{
	return this->impl_->get_hwnd();
}
