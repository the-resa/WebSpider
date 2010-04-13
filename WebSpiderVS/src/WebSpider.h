#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include "WebSpider/URL.h"

using namespace std;

class WebSpider {

public:
	WebSpider(string protocol, string host);
	void crawl(string link);
	vector<std::string> crawledLinks;
	vector<std::string> brokenLinks;

private:
	string protocol;
	string host;
};

#endif