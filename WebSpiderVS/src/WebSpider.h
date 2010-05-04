#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include "ThreadSafeVector.h"

using namespace std;
using namespace boost::asio::ip;

#define DEBUG
#define MULTITHREADING
#define THREAD_NUM 20

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string path, string file="");
	ThreadSafeVector<string> crawledLinks, brokenLinks;
	double elapsedTime;

private:
	string protocol;
	string host;
	string domain;
	boost::recursive_mutex mutex;
	boost::timer crawlTimer;
#ifdef MULTITHREADING
	bool createThreads;
	ThreadSafeVector<boost::thread*> threads;
#endif
};

#endif