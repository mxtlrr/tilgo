#include "gui/window.hpp"

Window::Window(){
	this->wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
	RegisterClassExW(&this->wc);
	this->hwnd = CreateWindowW(wc.lpszClassName, L"Flux", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, nullptr, nullptr, wc.hInstance, nullptr);
}

Window::~Window(){
	DestroyWindow(this->hwnd);
	UnregisterClassW(this->wc.lpszClassName, this->wc.hInstance);
}


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;

	switch (msg){
		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED) return 0;
			g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
			g_ResizeHeight = (UINT)HIWORD(lParam);
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
				::PostQuitMessage(0);
				return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

void Window_Status(Game g, PointerChains p){
	ImGui::Begin("Gameplay Status");
	ImGui::Text("Sun Amount: %ld", g.readMem<DWORD>(p.GetIndex(0)));
	ImGui::End();
}