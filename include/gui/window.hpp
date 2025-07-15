#pragma once

#include <Windows.h>
#include <iostream>
#include <cstdint>

#include "gui/imgui.hpp"

class Window {
	public:
		WNDCLASSEXW wc;
		HWND hwnd;

		Window();
		~Window();
};

extern bool checkbox_states[3];
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);