#include "WebSpider.h"

int main()
{

	WebSpider spider("http", "tv.vienna.at");
	spider.crawl("/");

	system("PAUSE");

	return 0;
}
