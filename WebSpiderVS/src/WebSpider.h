#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "ThreadSafeVector.h"

using namespace std;
using namespace boost::asio::ip;

#define DEBUG
//#define THREADING

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string path, string file="");
	ThreadSafeVector<string> crawledLinks, brokenLinks;

private:
	string protocol;
	string host;
	string domain;
	boost::mutex mutex;
#ifdef THREADING
	unsigned int threadNum;
#endif
};

#endif