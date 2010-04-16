#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "ThreadSafeVector.h"

using namespace std;
using namespace boost::asio::ip;

#define DEBUG

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string path, string link="");
	ThreadSafeVector<string> crawledLinks;
	ThreadSafeVector<string> brokenLinks;

private:
	string protocol;
	string host;
	string domain;
	boost::mutex mutex;
};

#endif