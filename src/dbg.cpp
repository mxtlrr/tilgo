#include "dbg.hpp"

std::vector<thread_t> threads;
void HandleDbg(DEBUG_EVENT* d){
	switch(d->dwDebugEventCode){
		case CREATE_THREAD_DEBUG_EVENT: {
			CREATE_THREAD_DEBUG_INFO i = d->u.CreateThread;
			threads.push_back((thread_t){
				.h = i.hThread, .start = i.lpStartAddress
			});
			printf("Thread created: %p (%d) threads now\n",
					i.lpStartAddress, threads.size());
			break;
		}
		
			case EXIT_THREAD_DEBUG_EVENT:
				break;
	}
}