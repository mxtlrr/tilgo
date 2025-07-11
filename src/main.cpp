#include <Windows.h>
#include "game.hpp"

#define UNUSED(x) (void)x

int main(void){
	Game g;

	std::printf("tilgo: game base %x\n", g.gamebase);
	return 0;
}