#include <Windows.h>
#include "game.hpp"
#include "ptr.hpp"
#include "dbg.hpp"
#define UNUSED(x) (void)x

/* ImGui */
#include "gui/window.hpp"

int main(void){
	// Initialize
	Game g;
	PointerChains p(&g);
	Window w;

	// Initialize Direct3D
	if (!CreateDeviceD3D(w.hwnd)){
		CleanupDeviceD3D();
		UnregisterClassW(w.wc.lpszClassName, w.wc.hInstance);
		return 1;
	}

	ShowWindow(w.hwnd, SW_SHOWDEFAULT);
	UpdateWindow(w.hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(w.hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	bool done = false;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	DEBUG_EVENT dbg;
	ZeroMemory(&dbg, sizeof(dbg));
	while(!done){
		// Are there any debug events?
		WaitForDebugEvent(&dbg, (int)(1000/60));
		HandleDbg(&dbg);

		// No? Continue executing as normal.
		ContinueDebugEvent(dbg.dwProcessId, dbg.dwThreadId, DBG_CONTINUE);

		MSG msg;
		while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			if(msg.message == WM_QUIT) done = true;
		}

		if (g_ResizeWidth != 0 && g_ResizeHeight != 0){
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
			g_ResizeWidth = g_ResizeHeight = 0;
			CreateRenderTarget();
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Show some windows!
		Window_Status(io, &g, &p);
		Mods(&g, &p);

		ImGui::Render();
		const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		HRESULT hr = g_pSwapChain->Present(1, 0);
		g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
	}

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupDeviceD3D();
	return 0;
}