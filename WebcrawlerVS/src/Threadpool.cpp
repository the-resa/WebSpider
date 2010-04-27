#include "Threadpool.h"

Threadpool::Threadpool(unsigned int threads) {
	for (unsigned int i = 0; i < threads; i++) {
		
	}
}

Threadpool::~Threadpool() {

}

void Threadpool::submitTask(Runnable *r) {
	tasks.push_back(r);
}

Runnable* Threadpool::getTask() {
	return tasks.front();
}