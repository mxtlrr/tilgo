#include <Windows.h>
#include "game.hpp"
#include "ptr.hpp"
#define UNUSED(x) (void)x

int main(void){
	Game g;
	PointerChains p(&g);

	return 0;
}