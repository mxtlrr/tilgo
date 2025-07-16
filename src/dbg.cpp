#include "dbg.hpp"

#define YES_UNICODE 1
#define NO_UNICODE  0

std::vector<thread_t> threads;
void HandleDbg(DEBUG_EVENT* d){
	switch(d->dwDebugEventCode){
		case CREATE_THREAD_DEBUG_EVENT: {
			CREATE_THREAD_DEBUG_INFO i = d->u.CreateThread;
			for(thread_t& t : threads){
				if(i.lpStartAddress == t.start || i.lpThreadLocalBase == t.base)
					return;
			}
			threads.push_back((thread_t){.h = i.hThread,
					.start = i.lpStartAddress, .base = i.lpThreadLocalBase});
					printf("flux debugger: thread created! Start: %p // Local base: %p\n",
					i.lpStartAddress, i.lpThreadLocalBase);
			break;
		}
		
			case EXIT_THREAD_DEBUG_EVENT: {
				// Check which thread is actually invalid
				for(DWORD i = 0; i < threads.size(); i++){
					if(threads[i].h == NULL){
						printf("flux debugger: thread %ld removed -- invalid.\n", i);
						threads.erase(threads.begin()+i);
					}
				}
				break;
			}


			case EXIT_PROCESS_DEBUG_EVENT:
				MessageBoxA(NULL, "Plants vs. Zombies has quit. Pressing 'OK' will kill Flux.",
							"WARNING", MB_ICONWARNING | MB_OK);
				exit(0);
				break;

			case OUTPUT_DEBUG_STRING_EVENT: {
				printf("flux debugger: recieved debug string event!\n");
				
				OUTPUT_DEBUG_STRING_INFO si = d->u.DebugString;
				if(si.fUnicode != YES_UNICODE){
					uint8_t* mm = (uint8_t*)malloc(si.nDebugStringLength+1);
					
					// Temporary handle for debugging
					HANDLE hDbg = OpenProcess(PROCESS_ALL_ACCESS, FALSE, d->dwProcessId);
					SIZE_T read = 0;
					ReadProcessMemory(hDbg, si.lpDebugStringData, mm, (si.nDebugStringLength+1), &read);
					printf("flux debugger: \"%s\"\n", mm);
					free(mm);
				}
				break;
			}

			default:
				printf("flux debugger: unhandled debug event %ld\n", d->dwDebugEventCode);
				break;
	}
}