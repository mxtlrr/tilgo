#include "ptr.hpp"


PointerChains::PointerChains(Game* g){
	printf("flux: resolving pointer chains...\n");
	this->Resolve(g, SUN_COUNT_OFF, sun_count_chain);
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


/***** ****/
std::vector<DWORD> sun_count_chain = {
	0x358, 0x14, 0x18, 0x4, 0x0, 0x68, 0x0, 0x74, 0x254, 0x5578
};