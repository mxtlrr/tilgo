#include "ptr.hpp"


PointerChains::PointerChains(Game* g){
	printf("flux: resolving pointer chains...\n");
	this->Resolve(g, SUN_COUNT_OFF, sun_count_chain);
	this->Resolve(g, LEVEL_OFF, level_off_chain);
	this->Resolve(g, CURRENCY_OFF, currency_off_chain);
}

uintptr_t PointerChains::Resolve(Game* g, uintptr_t off, std::vector<DWORD> chain){
	uintptr_t addr = g->readMem<uintptr_t>(g->gamebase + off);
	for(size_t i = 0; i < chain.size(); i++){
		addr += chain[i];
		if(i < chain.size() - 1) addr = g->readMem<uintptr_t>(addr);
	}

	this->ptr_chains.push_back(addr);
	printf("ptr chain: resolved to 0x%x\n", addr);
	return addr;
}

uintptr_t PointerChains::GetIndex(int index){
	return this->ptr_chains[index];
}

void PointerChains::ClearPointerChains(void){
	this->ptr_chains.clear();
}


/***** ****/
uint8_t pre_currency[7] = {
	0xC7, 0x40, 0x50, 0x9F, 0x86, 0x01, 0x00
};

uint8_t pre_sun[10] = {
	0xC7, 0x80, 0x78, 0x55, 0x00, 0x00, 0x06, 0x27, 0x00, 0x00
};

/****** ******/

std::vector<DWORD> sun_count_chain = {
	0x14, 0x90, 0x320, 0x30, 0x0, 0x8, 0x15C, 0x1bC, 0x5578
};

std::vector<DWORD> level_off_chain = {
	0x9c, 0x38, 0x0, 0x6c, 0x0, 0x7c
};

std::vector<DWORD> currency_off_chain = {
	0xA80
};