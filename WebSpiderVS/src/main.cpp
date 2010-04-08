#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "WebSpider.h"
#include "WebSpider/HTTP.h"

int main()
{
	WebSpider spider;
	spider.crawlURL("www.vollbeat.de");

	system("PAUSE");

	return 0;
}
