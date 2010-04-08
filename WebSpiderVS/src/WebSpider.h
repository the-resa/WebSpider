#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <vector>

using boost::asio::ip::tcp;
using namespace std;

class WebSpider {

public:
	string getHTTP(string server, string path);
	vector<string> brokenUrls;
};

#endif