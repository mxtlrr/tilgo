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

#define LEVEL_OFF 0x00326E14
extern std::vector<DWORD> level_off_chain;

#define CURRENCY_OFF 0x001378C4
extern std::vector<DWORD> currency_off_chain;

/* Addresses in memory that do stuff */
#define SUN_BOUNDS_CHECK 			  0x41E6F7 // Size: 10 bytes
#define CURRENCY_BOUNDS_CHECK   0x43376D // Size: 7 bytes
extern uint8_t pre_currency[7];
extern uint8_t pre_sun[10];

#define PAUSE_WHEN_NOT_IN_FOCUS 0x45272A // 0x74 -> disable, 0x75 enable
