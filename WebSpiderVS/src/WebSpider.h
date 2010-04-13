#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <string>
#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::asio::ip;

#define DEBUG

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string link);
	vector<string> crawledLinks;
	vector<string> brokenLinks;

private:
	string protocol;
	string host;
};

#endif