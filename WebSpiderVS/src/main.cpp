#include "WebSpider.h"
#include <boost/timer.hpp>

int main()
{
	WebSpider spider("http", "www.wrel.de");
	spider.crawl("/frick/Demosite/");
	system("PAUSE");
	return 0;
}
