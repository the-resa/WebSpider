#include "WebSpider.h"

int main()
{
<<<<<<< HEAD
	WebSpider spider;
	spider.crawlURL("www.fh-salzburg.ac.at");
=======

	WebSpider spider("http", "www.frick-web.at");
	spider.crawl("/Demosite/");
>>>>>>> 228c7f46d30a1f2cde3c69a3992ecb15284c9454

	system("PAUSE");

	return 0;
}
