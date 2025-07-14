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

void Window_Status(ImGuiIO& io, Game* g, PointerChains* p){
	ImGui::Begin("Gameplay Status");

	ImGui::Text("Sun Amount: %d", g->readMem<unsigned int>(p->GetIndex(SUN_COUNT)));
	DWORD level = g->readMem<DWORD>(p->GetIndex(LEVEL));
	ImGui::Text("Level: %d-%d\n", (int)((level+10)/10), (int)(level%10));
	ImGui::Text("$%d\n", g->readMem<int>(p->GetIndex(PVZ_CURRENCY))*10);

	ImGui::Text("FPS: %.2f", io.Framerate);
	ImGui::End();
}


void Mods(Game* g, PointerChains* p){
	ImGui::Begin("Mods");
	
	// Give sun
	static char give_sun_buf[50] = { 0 };
	ImGui::InputText("##", give_sun_buf, 15); ImGui::SameLine();
	if(ImGui::Button("Give Sun"))
		g->writeMem<DWORD>(std::atoi(give_sun_buf), p->GetIndex(0));

	// Change level
	static char change_level_buf[5] = { 0 };
	ImGui::InputText("##2", change_level_buf, 4); ImGui::SameLine();
	if(ImGui::Button("Change Level")){ // Assuming input is in the form "[WORLD]-[LEVEL]"
		uint8_t world = (change_level_buf[0])-0x30;
		uint8_t level = std::atoi(change_level_buf+2);
		DWORD resolved = ((world-1)*10) + level;
		
		g->writeMem<DWORD>(resolved, p->GetIndex(1));
	}

	// Fix pointers if they ever break.
	if(ImGui::Button("Re-resolve Pointers")){
		p->ClearPointerChains();
		p->Resolve(g, SUN_COUNT_OFF, sun_count_chain);
		p->Resolve(g, LEVEL_OFF, level_off_chain);
		p->Resolve(g, CURRENCY_OFF, currency_off_chain);
	}

	ImGui::End();
}