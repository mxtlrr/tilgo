#include "game.hpp"

DWORD getPID(std::string gameName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "[!] CreateToolhelp32Snapshot failed: " << GetLastError() << std::endl;
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &pe)) {
		do {
			if (_tcsicmp(pe.szExeFile, gameName.c_str()) == 0) {
				CloseHandle(hSnapshot);
				return pe.th32ProcessID;
			}
		} while (Process32Next(hSnapshot, &pe));
	}

	CloseHandle(hSnapshot);
	return 0;
}
uintptr_t getGameBase(DWORD procId) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (strcmp(modEntry.szModule, "popcapgame1.exe") == 0) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

Game::Game() {
	while(true){
		this->h = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
					FALSE, getPID("popcapgame1.exe"));
		if(this->h != INVALID_HANDLE_VALUE) break;

		printf("Failed to open process! (EC: %ld) Retrying...\n", GetLastError());
		Sleep(1000);
	}

	this->gamebase = getGameBase(getPID("popcapgame1.exe"));
}

Game::~Game(){
	CloseHandle(this->h);
}