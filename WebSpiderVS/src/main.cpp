#include "WebSpider.h"

int main()
{
	WebSpider spider("http", "www.wrel.de");
	spider.crawl("/frick/Demosite/");

	system("PAUSE");

	return 0;
}
