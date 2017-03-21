#include "Macros.h"

BuildWindow::BuildWindow() {
	MakeWindow();
}

BuildWindow::~BuildWindow() {
	KillWindow();
}

void KeyDown(uint8_t key) {
	if (GetAsyncKeyState(VK_ESCAPE))
		exit(0);
}

LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYDOWN:
		KeyDown(static_cast<uint8_t>(wParam));
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void BuildWindow::MakeWindow() {
	hInstance = GetModuleHandle(nullptr);
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";
	RegisterClassEx(&wc);
	hWnd = CreateWindow(wc.lpszClassName, "lunarEngine",
		WS_SYSMENU | WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - 1038) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 583) / 2,
		1038, 583, nullptr, nullptr, hInstance, 0);
}

void BuildWindow::KillWindow() {
	DestroyWindow(hWnd);
	UnregisterClass("WindowClass", hInstance);
}
