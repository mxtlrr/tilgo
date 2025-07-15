#include "dbg.hpp"

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
		
			case EXIT_THREAD_DEBUG_EVENT:
				// Check which thread is actually invalid
				for(DWORD i = 0; i < threads.size(); i++){
					if(threads[i].h == NULL){
						printf("flux debugger: thread %ld removed -- invalid.\n", i);
						threads.erase(threads.begin()+i);
					}
				}
				break;

			

			default:
				printf("flux debugger: unhandled debug event %02ld\n",
					d->dwDebugEventCode);
				break;
	}
}