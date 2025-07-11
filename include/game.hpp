#pragma once

#include <windows.h>
#include <vector>
#include <Psapi.h>
#include <tchar.h>
#include <cstdint>
#include <limits.h>
#include <iostream>
#include <tlhelp32.h>


DWORD getPid(std::string name);
uintptr_t getGameBase(DWORD pid);

class Game {
	public:
		HANDLE h;
		uintptr_t gamebase;

		Game();
		~Game();
		
		template <typename T>
		T readMem(uintptr_t loc){
			T k;
			ReadProcessMemory(this->h, reinterpret_cast<LPCVOID>(loc), &k, sizeof(k), NULL);
			return k;
		}

		template <typename T>
		void writeMem(T k, uintptr_t loc){
			WriteProcessMemory(this->h, reinterpret_cast<LPVOID>(loc), &k, sizeof(k), NULL);
		}
};