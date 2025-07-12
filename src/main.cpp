#include <Windows.h>
#include "game.hpp"
#include "ptr.hpp"
#define UNUSED(x) (void)x

int main(void){
	Game g;
	PointerChains p(&g);

	printf("%ld", g.readMem<DWORD>(p.GetIndex(0)));
	return 0;
}