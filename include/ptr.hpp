#pragma once

#include <windows.h>
#include <vector>
#include <cstdint>
#include <limits.h>
#include <iostream>

#include "game.hpp"

enum PtrChainIndices {
	SUN_COUNT = 0
};

class PointerChains {
	private:
		std::vector<uintptr_t> ptr_chains;
	public:
		PointerChains(Game* g);
		uintptr_t Resolve(Game* g, uintptr_t off, std::vector<DWORD> chain);
		uintptr_t GetIndex(int index);
};


/* Pointers */
#define SUN_COUNT_OFF 0x010D8C4
extern std::vector<DWORD> sun_count_chain;