#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "WebSpider/WebSpider.h"

int main()
{

	Link startLink("http://www.fh-salzburg.ac.at");
	WebSpider spider;
	spider.crawl(startLink);

	system("PAUSE");

	return 0;
}
