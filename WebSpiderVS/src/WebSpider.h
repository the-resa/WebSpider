#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <vector>

#include "WebSpider/HTMLParser.h"

using boost::asio::ip::tcp;
using namespace std;

class WebSpider {

public:
	void crawlURL(string server);
	string getHTTP(string server, string path);
	vector<string> brokenURLs;
	vector<string> crawledURLs;
	HTMLParser htmlParser;
};

#endif