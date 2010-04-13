#include "WebSpider.h"

int main()
{

	WebSpider spider("http", "www.frick-web.at");
	spider.crawl("/Demosite/");

	system("PAUSE");

	return 0;
}
