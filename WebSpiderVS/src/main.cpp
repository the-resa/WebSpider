#include "WebSpider.h"
#include <boost/timer.hpp>

int main()
{
	WebSpider spider("http", "www.webreload.de");
	spider.crawl("/");
	cout << "Elapsed time: " << spider.elapsedTime << " seconds\n";
	cout << "Links crawled: " << spider.crawledLinks.size() << endl;
	cout << "Broken links found: " << spider.brokenLinks.size() << endl;
	system("PAUSE");
	return 0;
}
