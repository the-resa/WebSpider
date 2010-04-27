#ifndef WEB_CRAWLER_H
#define WEB_CRAWLER_H

#include "Threadpool.h"

class WebCrawler {

public:
	void thread_func(void* arg);
	Threadpool threadpool;
};


#endif