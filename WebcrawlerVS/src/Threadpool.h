#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <deque>
#include <boost/thread.hpp>
#include "Runnable.h"

class Threadpool {
public:
	Threadpool(unsigned int nthreads = 2);
	~Threadpool();

	void submitTask(Runnable *r);
	Runnable *getTask();

private:
	bool shutdown;
	boost::mutex tasks_mutex;
	boost::condition_variable tasks_cond;
	std::deque<Runnable *> tasks;
	std::vector<boost::thread> threads;
};

#endif
