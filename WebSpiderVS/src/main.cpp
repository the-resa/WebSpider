#include "WebSpider.h"

int main()
{
	WebSpider spider("http", "www.frick-web.at");
	spider.crawl("/Demosite/");

	cout << "Links crawled: " << spider.crawledLinks.size() << endl;
	cout << "Broken links found: " << spider.brokenLinks.size() << endl;

	system("PAUSE");

	return 0;
}
