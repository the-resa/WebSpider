#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <deque>

class Threadpool {
	public:
		Threadpool(unsigned int nthreads = 2);
		~Threadpool();

	void submitTask(Runnable *r);
		Runnable *getTask();

	private:
		bool shutdown;
		pthread_mutex_t tasks_mutex;
		pthread_cond_t tasks_cond;
		std::deque<Runnable *> tasks;
		std::vector<pthread_t> threads;
};

#endif
