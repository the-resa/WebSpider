#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "WebSpider/WebSpider.h"

int main()
{
	WebSpider spider;
	spider.crawlURL("www.fh-salzburg.ac.at");

	system("PAUSE");

	return 0;
}
