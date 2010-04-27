#include "WebCrawler.h"

void WebCrawler::thread_func(void *arg) {
	Threadpool *tp = (Threadpool *) arg;
	if (!tp) return;

	while (true) {
		Runnable *r = tp->getTask();
		if (!r) break;
		r->run();
		delete r;
	}
	return;
}