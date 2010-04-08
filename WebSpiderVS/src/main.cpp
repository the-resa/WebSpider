#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "WebSpider/HTTPGetter.h"

using namespace std;


int main()
{
	HTTPGetter http;
	http.get_http("www.wrel.de","/");

 system("PAUSE");
}
