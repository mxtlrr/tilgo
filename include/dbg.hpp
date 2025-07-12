#pragma once

#include <Windows.h>
#include <cstdint>
#include <vector>
#include <d3d11.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "game.hpp"

typedef struct {
	HANDLE h;
	LPTHREAD_START_ROUTINE start;
} thread_t;

extern std::vector<thread_t> threads;
void HandleDbg(DEBUG_EVENT* d);