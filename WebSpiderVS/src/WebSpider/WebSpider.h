#ifndef WEB_SPIDER_H
#define WEB_SPIDER_H

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <vector>

#include "HTML.h"
#include "Link.h"

#define CRAWL_DOMAIN_ONLY

using boost::asio::ip::tcp;
using namespace std;

class WebSpider {

public:
	void crawl(Link link);

	vector<Link> brokenLinks;
	vector<Link> crawledLinks;
};

#endif