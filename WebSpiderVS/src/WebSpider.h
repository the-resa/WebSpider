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
#define MAX_THREAD_NUM 40

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string path, string file="");
	ThreadSafeVector<string> crawledLinks, brokenLinks;
	double elapsedTime;
	unsigned int getThreadNum() const;

private:
	string protocol;
	string host;
	string domain;
	boost::recursive_mutex mutex;
	unsigned int threadNum;
	void _crawl(string path, string file);	// wraps the crawl-function
};

#endif