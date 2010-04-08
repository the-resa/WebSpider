#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "WebSpider.h"
#include "WebSpider/HTTP.h"

int main()
{
	WebSpider spider;
	HTTP http(spider.getHTTP("www.wrel.de","/"));

	std::cout << http.getData();

	system("PAUSE");

	return 0;
}
