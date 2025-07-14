#pragma once

#include <windows.h>
#include <vector>
#include <cstdint>
#include <limits.h>
#include <iostream>

#include "game.hpp"

enum PtrChainIndices {
	SUN_COUNT     = 0,
	LEVEL         = 1,
	PVZ_CURRENCY  = 2
};

class PointerChains {
	private:
		std::vector<uintptr_t> ptr_chains;
	public:
		PointerChains(Game* g);
		uintptr_t Resolve(Game* g, uintptr_t off, std::vector<DWORD> chain);
		uintptr_t GetIndex(int index);
		void ClearPointerChains(void);
};


/* Pointers */
#define SUN_COUNT_OFF 0x00326658
extern std::vector<DWORD> sun_count_chain;

#define LEVEL_OFF 0x00329728
extern std::vector<DWORD> level_off_chain;

#define CURRENCY_OFF 0x00329698
extern std::vector<DWORD> currency_off_chain;

/* Addresses in memory that do stuff */
#define SUN_BOUNDS_CHECK 0x41E6F7 // Size: 10 bytes


// coin addition for normal coins: 0x43375f <-- add [eax+50], edx
// sub_4336C0 v2:
//		Sunflower:   v2 = 4
//    Sun Shroom:  v2 = ?
//		Yellow Coin: v2 = 2
//		White Coin:  v2 = 1