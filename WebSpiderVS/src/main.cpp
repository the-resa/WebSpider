#include "WebSpider.h"

int main()
{
	WebSpider spider("http", "www.fh-salzburg.ac.at");
	spider.crawl("/");

	cout << "Links crawled: " << spider.crawledLinks.size() << endl;
	cout << "Broken links found: " << spider.brokenLinks.size() << endl;

	return 0;
}
