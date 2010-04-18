#include "WebSpider.h"

int main()
{
	WebSpider spider("http", "www.wrel.de");
	spider.crawl("/frick/regex/");

	cout << "Links crawled: " << spider.crawledLinks.size() << endl;
	cout << "Broken links found: " << spider.brokenLinks.size() << endl;

	system("PAUSE");
	return 0;
}
