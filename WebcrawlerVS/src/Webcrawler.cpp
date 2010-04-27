#include "Webcrawler.h"


void *thread_func(void *arg) {
	Threadpool *tp = (Threadpool *) arg;
	if (!tp) return 0;

	while (true) {
		Runnable *r = tp->getTask();
		if (!r) break;
		r->run();
		delete r;
	}
	return 0;
}