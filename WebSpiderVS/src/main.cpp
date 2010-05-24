#include "WebSpider.h"
#include <boost/timer.hpp>
#include <ctime>

int main()
{
	time_t start, end;
	WebSpider spider("http", "www.wrel.de");

	time(&start);
	spider.crawl("/frick/Demosite/");

	while (true) {
		if (0 == spider.getThreadNum()) {
			Sleep(1000); // sleep one second to wait if there are still threads running
			if (0 == spider.getThreadNum()) {
				break;
			}
		}
	}

	time(&end);

	std::cout << "Links crawled: " << spider.crawledLinks.size() << std::endl;
	std::cout << "Broken links found: " << spider.brokenLinks.size() << std::endl;
	std::cout << "Broken links in percent: " << (float)spider.brokenLinks.size() / (float)spider.crawledLinks.size() * 100 << std::endl;
	std::cout << "Elapsed time: " << difftime(end, start) << std::endl;

	system("PAUSE");
	return 0;
}
