
#include "../device.h"

#ifdef _WIN32

namespace dream
{

WindowScreen::WindowScreen(HINSTANCE hInstance) :
	hInstance(hInstance),
	Screen()
{
	this->DefWindowClassEx(wcex);
}

void WindowScreen::Setup(void)
{
	// 登録に失敗したら例外を発生させます。
	::RegisterClassEx(&this->wcex);

	// クライアントサイズを取得
	RECT crect = {0, 0, this->screen_width, this->screen_height};
	AdjustWindowRectEx(
		&crect, 
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 
		FALSE,
		NULL);

	// 中央を取得
	RECT dtRect;
	HWND desktop = ::GetDesktopWindow();
	::GetWindowRect(desktop, &dtRect);

	// ウィンドウを生成
	this->hwnd = ::CreateWindow(
		this->wcex.lpszClassName,
		WindowStringConverter::GetConvertString(this->title.c_str()).get(),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
		(dtRect.right - (crect.right - crect.left)) / 2,
		(dtRect.bottom - (crect.bottom - crect.top)) / 2,
		this->screen_width,
		this->screen_height,
		NULL,
		NULL,
		this->hInstance,
		NULL);

	// ウィンドウの表示
	::ShowWindow(this->hwnd, SW_SHOW);
	::UpdateWindow(this->hwnd);
}

ScreenResult WindowScreen::Update(void)
{

	MSG msg;

	// Windowsアプリケーション手続き
	if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{

		if (::GetMessage(&msg, NULL, 0, 0) == NULL)
		{
			// メインループを抜ける処理
			return ScreenResult::Exit;
		}

		::DispatchMessage(&msg);
		::TranslateMessage(&msg);

		return ScreenResult::Wait;
	}
	else
	{
		return ScreenResult::Run;
	}

}

void WindowScreen::Release(void)
{

}

void WindowScreen::DefWindowClassEx(WNDCLASSEX& wcex)
{
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance		= this->hInstance;
	wcex.lpszClassName	= L"nightmare_lib_class";
	wcex.lpfnWndProc	= (WNDPROC) DefWndProc;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH) (COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
}

void WindowScreen::SetScreenTitle(const char* title)
{
	this->title = std::string(title);
	::SetWindowText(this->hwnd, WindowStringConverter::GetConvertString(title).get());
}

void WindowScreen::ShowScreen(bool enable)
{
	::ShowWindow(this->hwnd, enable ? SW_SHOW : SW_HIDE);
	::UpdateWindow(this->hwnd);
}

LRESULT CALLBACK WindowScreen::DefWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{

	switch (msg)
	{

	case WM_DESTROY:
	{
		::PostQuitMessage(0);
	}
	break;

	default:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	break;

	}

	return 0;
}

} // namespace dream

#endif // _WIN32
